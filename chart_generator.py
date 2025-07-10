## got all the file format data from https://www.celersms.com/doc/XM_file_format.pdf 
## and https://www.fileformat.info/format/xm/corion.htm
## mostly using hex for positions and dec for lengths, but my two references use opposites so I might be inconsistent

import os
import string

class ChartGenerator:
    def __init__(self, directory):
        self.directory = directory

    def parse_xm(self):
        self.output = ""
        self.cpp_header()
        for filename in os.listdir(self.directory):
            self.filename = os.path.join(self.directory, filename)
            if filename.endswith('.xm'):
                with open(self.filename, "rb") as file:
                    self.file = file
                    self.parse_song_name()
                    self.read_header()
                    self.read_patterns()
                    self.song_details()
        self.cpp_footer()
        self.write_to_file()

    def parse_song_name(self):
        name = os.path.basename(self.filename)
        self.name_underscore = name.split('.')[0]
        name_spaces = self.name_underscore.replace('_', ' ')
        self.song_name = string.capwords(name_spaces)
        print(f"Song Name: {self.song_name}")

    def read_header(self):
        file = self.file
        file.seek(0x3C)
        self.header_size = int.from_bytes(file.read(4), byteorder='little')
        self.song_length = int.from_bytes(file.read(2), byteorder='little')

        file.seek(0x44)
        self.num_channels = int.from_bytes(file.read(2), byteorder='little')
        self.num_patterns = int.from_bytes(file.read(2), byteorder='little')

        # pulling out the tempo, which seems to be the bpm I set in the music software
        # no clue what the 'BPM' value is in the .xm data, but I'm going to ignore it for now
        file.seek(0x4E)
        self.default_tempo = int.from_bytes(file.read(2), byteorder='little')
        print(f"Tempo: {self.default_tempo}")

        file.seek(0x50)
        self.pattern_order = []
        for i in range(min(self.song_length, self.header_size - 0x50)):
            order = int.from_bytes(file.read(1), byteorder='little')
            self.pattern_order.append(order)
        print(f"Pattern Order: {self.pattern_order}")
        
    def read_patterns(self):
        file = self.file
        start_of_patterns = self.header_size + 60
        notes = []
        row_offset = 0 # this isn't a memory location, just a number to see what we should add to the row number. Should probs change name when I get a chance
        for pattern_num in self.pattern_order:
            # Skip to the correct pattern
            file.seek(start_of_patterns)
            for i in range(pattern_num):
                current_offset = file.tell()
                pattern_header_size = pattern_header_size = int.from_bytes(file.read(4), byteorder='little')
                file.seek(file.tell() + 1) # ignore packing type byte - apparently meaningless
                num_rows = int.from_bytes(file.read(2), byteorder='little')
                pattern_size = int.from_bytes(file.read(2), byteorder='little')
                file.seek(current_offset + pattern_header_size + pattern_size) # jump to next pattern header

            current_offset = file.tell()
            pattern_header_size = pattern_header_size = int.from_bytes(file.read(4), byteorder='little')
            file.seek(file.tell() + 1) # ignore packing type byte - apparently meaningless
            num_rows = int.from_bytes(file.read(2), byteorder='little')
            pattern_size = int.from_bytes(file.read(2), byteorder='little')

            file.seek(current_offset + pattern_header_size) # jump to pattern data

            pattern_data = file.read(pattern_size)
            
            pos = 0
            current_row = 0
            cells_in_row = 0

            while pos < pattern_size and current_row < num_rows:
                note = 0
                instrument = 0

                # MSB = 1 in compressed data
                compression_byte = pattern_data[pos]
                pos += 1
                if compression_byte & 0x80:
                    # note is compressed, need to pluck out the individual pieces (if they exist, anyway)
                    if compression_byte & 0x1:
                        note = pattern_data[pos]
                        pos += 1
                    if compression_byte & 0x2:
                        instrument = pattern_data[pos]
                        pos += 1
                    if compression_byte & 0x4:
                        volume = pattern_data[pos]
                        pos += 1
                    if compression_byte & 0x8:
                        effect = pattern_data[pos]
                        pos += 1
                    if compression_byte & 0x10:
                        effect_param = pattern_data[pos]
                        pos += 1
                else:
                    note = compression_byte
                    instrument = pattern_data[pos]
                    pos += 4

                # .xm file doesn't tell us which channel a note is in so we track it here
                # this is, as far as I could figure out, the only way to know which row you're on
                cells_in_row += 1
                if cells_in_row >= self.num_channels:
                    cells_in_row = 0
                    current_row += 1

                # Instrument 1 is the instrument used to track notes by whoever makes the actual music
                # note 0 means no note is being played
                if (instrument == 1) and (note > 0):
                    match note % 12:
                        case 0: # B
                            button = "bn::keypad::key_type::UP"
                        case 1: # C
                            button = "bn::keypad::key_type::R"
                        case 2: # C#
                            button = "bn::keypad::key_type::A"
                        case 3: # D
                            button = "bn::keypad::key_type::R"
                        case 4: # D#
                            button = "bn::keypad::key_type::DOWN"
                        case 5: # E
                            button = "bn::keypad::key_type::L"
                        case 6: # F
                            button = "bn::keypad::key_type::R"
                        case 7: # F#
                            button = "bn::keypad::key_type::B"
                        case 8: # G
                            button = "bn::keypad::key_type::LEFT"
                        case 9: # G#
                            button = "bn::keypad::key_type::L"
                        case 10: # A
                            button = "bn::keypad::key_type::RIGHT"
                        case 11: # A#
                            button = "bn::keypad::key_type::UP"
                           
                    notes.append([button, current_row + row_offset, 1])
            row_offset += num_rows

        self.note_count = len(notes)
        print(f"Total Notes: {self.note_count}")

        # Process notes into C++ config format
        length = len(notes)
        output = f"    constexpr bn::array<note_data, {length}> {self.name_underscore}_data = {{{{\n"

        for i, note in enumerate(notes):
            button = note[0]
            row = note[1]
            speed = note[2]

            line = f"        {{{button}, {row}, {speed}}}" # apparently double {{ escapes, so this gives us single {} around the values

            if i < length - 1:
                line += ","
            
            output += line + "\n"

        output += "    }};\n\n"    
        self.output += output
        
    def song_details(self):
        output = f"    constexpr song {self.name_underscore} = {{\n"
        output += f"        {self.name_underscore}_data.data(),\n"
        output += f"        {self.name_underscore}_data.size(),\n"
        output += f"        {self.default_tempo},\n"
        output += f"        \"{self.song_name}\",\n"
        output += f"        normal\n"
        output += "    };\n\n"
        self.output += output

    def cpp_header(self):
        # this is a bit gross to look at bc of the indenting, but was the easiest way to do this in one string
        header = """#ifndef SONG_DATA_H
#define SONG_DATA_H

#include \"bn_array.h\"
#include \"bn_keypad.h\"
#include \"songs.h\"

namespace songs
{\n"""
        self.output += header

    def cpp_footer(self):
        footer = """}
#endif // SONG_DATA_H"""
        self.output += footer

    def write_to_file(self):
        try:
            with open("include/rhythm_game/song_data.h", "w") as file:
                file.write(self.output)
            print("Song charts successfully generated and written to include/rhythm_game/song_data.h")
        except IOError as e:
            print(f"Error writing to song_data.h: {e}")

gen = ChartGenerator("audio")
gen.parse_xm()
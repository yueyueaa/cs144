#include "stream_reassembler.hh"

#include <iostream>
// Dummy implementation of a stream reassembler.

// For Lab 1, please replace with a real implementation that passes the
// automated checks run by `make check_lab1`.

// You will need to add private members to the class declaration in `stream_reassembler.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&.../* unused */) {}

using namespace std;

StreamReassembler::StreamReassembler(const size_t capacity) : _output(capacity), _capacity(capacity) {}

//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.
void StreamReassembler::push_substring(const string &data, const size_t index, const bool eof) {
    // DUMMY_CODE(data, index, eof);
    size_t data_len = data.length();
    if(eof == true) {
        flag = true;
        stream_end = data_len +index;
    }



    if (pos_index == stream_end && flag)  //
        _output.end_input();
    /*
    size_t data_len = data.length();
    if (eof == true) {
        flag = true;
        stream_end = data_len + index;
    }
    for (size_t i = 0; i < data_len; i++) {
        if (index + i >= pos_index) {
            if (mp.find(index + i) == mp.end())
                string_len++;
            mp[index + i] = data[i];
        }
    }
    size_t pos = pos_index;
    string str_stream = "";
    for (auto it = mp.begin(); it != mp.end(); it++) {
        if (it->first != pos) break;
        if (down_mp[it->first] == 0) {
            if (str_stream.length() + 1 + _output.buffer_size() <= _capacity) {
                str_stream += it->second;
                down_mp[it->first] = 1;
                if (string_len > 0)
                    string_len--;
            }
        }
        pos++;
    }
    _output.write(str_stream);
    for (size_t i = 0; i < str_stream.length(); i++) {
        auto it = mp.begin();
        mp.erase(it);
    }
    pos_index += str_stream.length();
    if (pos_index == stream_end && flag)
        _output.end_input();
    */
}

size_t StreamReassembler::unassembled_bytes() const { return string_len; }

bool StreamReassembler::empty() const { return true; }

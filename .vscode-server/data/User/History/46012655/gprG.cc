#include "stream_reassembler.hh"

#include <cassert>

// Dummy implementation of a stream reassembler.

// For Lab 1, please replace with a real implementation that passes the
// automated checks run by `make check_lab1`.

// You will need to add private members to the class declaration in `stream_reassembler.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&.../* unused */) {}

using namespace std;

StreamReassembler::StreamReassembler(const size_t capacity)
    : 
    //str_map()
    //, next_loaded(0)
    //, string_len(0)
    //, _eof_idx(-1)
    _output(capacity)
    , _capacity(capacity) {}

//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.
void StreamReassembler::push_substring(const string &data, const size_t index, const bool eof) {
    auto str_pos = str_map.upper_bound(index);
    if (str_pos != str_map.begin())
        str_pos--;
    size_t new_idx = index;
    if (str_pos != str_map.end() && str_pos->first <= index) {
        const size_t up_idx = str_pos->first;
        if (index < up_idx + str_pos->second.size())
            new_idx = up_idx + str_pos->second.size();
    }
    else if (index < next_loaded)
        new_idx = next_loaded;
    const size_t data_start_pos = new_idx - index;
    ssize_t data_size = data.size() - data_start_pos;
    str_pos = str_map.lower_bound(new_idx);
    while (str_pos != str_map.end() && new_idx <= str_pos->first) {
        const size_t data_end_pos = new_idx + data_size;
        if (str_pos->first < data_end_pos) {
            if (data_end_pos < str_pos->first + str_pos->second.size()) {
                data_size = str_pos->first - new_idx;
                break;
            }
            else {
                string_len -= str_pos->second.size();
                str_pos = str_map.erase(str_pos);
                continue;
            }
        }
        else break;
    }
    size_t first_unacceptable_idx = next_loaded + _capacity - _output.buffer_size();
    if (first_unacceptable_idx <= new_idx)
        return;
    if (data_size > 0) {
        const string new_data = data.substr(data_start_pos, data_size);
        if (new_idx == next_loaded) {
            const size_t write_byte = _output.write(new_data);
            next_loaded += write_byte;
            if (write_byte < new_data.size()) {
                const string data_to_store = new_data.substr(write_byte, new_data.size() - write_byte);
                string_len += data_to_store.size();
                str_map.insert(make_pair(next_loaded, move(data_to_store)));
            }
        } else {
            const string data_to_store = new_data.substr(0, new_data.size());
            string_len += data_to_store.size();
            str_map.insert(make_pair(new_idx, move(data_to_store)));
        }
    }
    for (auto iter = str_map.begin(); iter != str_map.end(); /* nop */) {
        assert(next_loaded <= iter->first);
        if (iter->first == next_loaded) {
            const size_t write_num = _output.write(iter->second);
            next_loaded += write_num;
            if (write_num < iter->second.size()) {
                string_len += iter->second.size() - write_num;
                str_map.insert(make_pair(next_loaded, move(iter->second.substr(write_num))));
                string_len -= iter->second.size();
                str_map.erase(iter);
                break;
            }
            string_len -= iter->second.size();
            iter = str_map.erase(iter);
        }
        else break;
    }
    if (eof)
        _eof_idx = index + data.size();
    if (_eof_idx <= next_loaded)
        _output.end_input();
}

size_t StreamReassembler::unassembled_bytes() const { return string_len; }

bool StreamReassembler::empty() const { return string_len == 0; }
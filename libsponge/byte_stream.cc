#include "byte_stream.hh"
#include <iostream>
// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&.../* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) {  // DUMMY_CODE(capacity);
    len = capacity;
}

size_t ByteStream::write(const string &data) {
    // DUMMY_CODE(data);
    size_t l = data.length();
    if (l <= remaining_capacity()) {
        for (size_t i = 0; i < l; i++) {
            dq.push_back(data[i]);
        }
        write_num += l;
        return l;
    }
    size_t ll = remaining_capacity();
    for (size_t i = 0; i < ll; i++) {
        dq.push_back(data[i]);
    }
    write_num += ll;
    return ll;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len_out) const {
    // DUMMY_CODE(len);
    string buffer_output = "";
    if (len_out <= buffer_size()) {
        for (size_t i = 0; i < len_out; i++) {
            buffer_output += dq[i];
        }
        return buffer_output;
    }
    for (size_t i = 0; i < buffer_size(); i++) {
        buffer_output += dq[i];
    }
    return buffer_output;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len_out) {
    // DUMMY_CODE(len);
    for (size_t i = 0; i < len_out; i++) {
        read_num++;
        dq.pop_front();
    }
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len_out) {
    // DUMMY_CODE(len);  
    string tempstr = peek_output(len_out);
    //read_num += tempstr.length();
    pop_output(tempstr.length());
    return tempstr;
}

void ByteStream::end_input() { _end_in = true; }

bool ByteStream::input_ended() const { return _end_in; }

size_t ByteStream::buffer_size() const { return dq.size(); }

bool ByteStream::buffer_empty() const { return dq.empty(); }

bool ByteStream::eof() const {
    //cerr << "dq.empty()=="<<dq.empty()<<" "<<_end_in<<endl;
    if (dq.empty() && _end_in)
        return true;
    return false;
}

size_t ByteStream::bytes_written() const { return write_num; }

size_t ByteStream::bytes_read() const { return read_num; }

size_t ByteStream::remaining_capacity() const { return len - dq.size(); }

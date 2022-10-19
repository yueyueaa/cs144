#include "tcp_receiver.hh"
#pragma GCC diagnostic ignored "-Wunused-private-field"
// Dummy implementation of a TCP receiver

// For Lab 2, please replace with a real implementation that passes the
// automated checks run by `make check_lab2`.

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

void TCPReceiver::segment_received(const TCPSegment &seg) {
    //DUMMY_CODE(seg);
    TCPHeader header = seg.header();
    if (header.syn && bool_syn) return;
    if (header.syn) {
        bool_syn = true;
        seg_isn = header.seqno.raw_value();
    }
    if (header.fin && bool_syn)
        bool bool_fin = true;
    size_t seq_num = unwrap(header.seqno, WrappingInt32(seg_isn), _checkpoint);
    if(header.syn == 0) {
        seg_reassembler.push_substring(seg.payload().copy(), seq_num - 1); //seq-1是没传的值
    }
    else seg_reassembler.push_substring(seg.payload().copy(), header.fin);  
    _checkpoint = seq_num;
}

optional<WrappingInt32> TCPReceiver::ackno() const { size_t shift = 1;
    if (_fin && _reassembler.unassembled_bytes() == 0)
        shift = 2;
    if (_syn)
        return wrap(_reassembler.first_unassembled() + shift, WrappingInt32(_isn));
    return {};return {}; }

size_t TCPReceiver::window_size() const { 
    return _capacity - stream_out().buffer_size();
    return {}; }



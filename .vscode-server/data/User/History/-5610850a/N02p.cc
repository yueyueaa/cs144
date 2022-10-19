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
    if (header.syn && b_syn) return;
    if (header.syn) {
        b_syn = true;
        seg_isn = header.seqno.raw_value();
    }
    if (header.fin && b_syn) b_fin = true;
    size_t seq_num = unwrap(header.seqno, WrappingInt32(seg_isn), _checkpoint);
    if(header.syn == 0) {
        seg_reassembler.push_substring(seg.payload().copy(), seq_num - 1); //seq-1是没传的值
    }
    else seg_reassembler.push_substring(seg.payload().copy(), header.fin);  
    _checkpoint = seq_num;
}

optional<WrappingInt32> TCPReceiver::ackno() const { 
    size_t add = 1;
    if (b_fin && seg_reassembler.unassembled_bytes() == 0) add++;
    if (b_syn) return wrap(seg_reassembler.first_unassembled() + add, WrappingInt32(seg_isn));
    return {}; 
}

size_t TCPReceiver::window_size() const { 
    return _capacity - stream_out().buffer_size();
}



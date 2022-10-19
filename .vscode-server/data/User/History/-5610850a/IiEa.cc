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
        s_isn = header.seqno.raw_value();
    }
    if (header.fin && b_syn) b_fin = true;
    size_t seq_num = unwrap(header.seqno, WrappingInt32(s_isn), seg_checkpoint);
    if(header.syn) {
        _reassembler.push_substring(seg.payload().copy(), 0, header.fin); //seq-1是没传的值
    }
    else _reassembler.push_substring(seg.payload().copy(), seq_num-1, header.fin);  
    seg_checkpoint = seq_num;
}

optional<WrappingInt32> TCPReceiver::ackno() const { 
    size_t add = 1;
    if (b_fin && _reassembler.unassembled_bytes() == 0) add++;
    if (b_syn) return wrap(_reassembler + add, WrappingInt32(s_isn));
    return {}; 
}

size_t TCPReceiver::window_size() const { 
    return _capacity - stream_out().buffer_size();
}



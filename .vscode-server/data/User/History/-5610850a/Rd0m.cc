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
    // note that fin flag seg can carry payload
    if (bool_syn && header.fin)
        _fin = true;
    size_t absolute_seqno = unwrap(header.seqno, WrappingInt32(_isn), _checkpoint);
    _reassembler.push_substring(seg.payload().copy(), header.syn ? 0 : absolute_seqno - 1, header.fin);
    _checkpoint = absolute_seqno;


}

optional<WrappingInt32> TCPReceiver::ackno() const { return {}; }

size_t TCPReceiver::window_size() const { return {}; }



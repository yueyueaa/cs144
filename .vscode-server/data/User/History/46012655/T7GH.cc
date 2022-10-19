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
    : str_map()
    , next_loaded(0)
    , string_len(0)
    , _eof_idx(-1)
    , _output(capacity)
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
    // 当前子串将保存的 data 的长度

    ssize_t data_size = data.size() - data_start_pos;

    // 获取当前子串的下个子串时，需要考虑到 new_idx 可能会和 down_idx 重合
    str_pos = str_map.lower_bound(new_idx);
    // 下面注释的这两条语句与上面的 lower_bound 等价
    // if (str_pos != str_map.end() && str_pos->first <= new_idx)
    //     ++str_pos;

    // 如果和下面的子串冲突，则截断长度
    while (str_pos != str_map.end() && new_idx <= str_pos->first) {
        const size_t data_end_pos = new_idx + data_size;
        // 如果存在重叠区域
        if (str_pos->first < data_end_pos) {
            // 如果是部分重叠
            if (data_end_pos < str_pos->first + str_pos->second.size()) {
                data_size = str_pos->first - new_idx;
                break;
            }
            // 如果是全部重叠
            else {
                string_len -= str_pos->second.size();
                str_pos = str_map.erase(str_pos);
                continue;
            }
        }
        // 如果不重叠则直接 break
        else
            break;
    }
    size_t first_unacceptable_idx = next_loaded + _capacity - _output.buffer_size();
    if (first_unacceptable_idx <= new_idx)
        return;

    // 判断是否还有数据是独立的， 顺便检测当前子串是否被上一个子串完全包含
    if (data_size > 0) {
        const string new_data = data.substr(data_start_pos, data_size);
        // 如果新字串可以直接写入
        if (new_idx == next_loaded) {
            const size_t write_byte = _output.write(new_data);
            next_loaded += write_byte;
            // 如果没写全，则将其保存起来
            if (write_byte < new_data.size()) {
                // _output 写不下了，插入进 str_map 中
                const string data_to_store = new_data.substr(write_byte, new_data.size() - write_byte);
                string_len += data_to_store.size();
                str_map.insert(make_pair(next_loaded, std::move(data_to_store)));
            }
        } else {
            const string data_to_store = new_data.substr(0, new_data.size());
            string_len += data_to_store.size();
            str_map.insert(make_pair(new_idx, std::move(data_to_store)));
        }
    }

    // 一定要处理重叠字串的情况
    for (auto iter = str_map.begin(); iter != str_map.end(); /* nop */) {
        // 如果当前刚好是一个可被接收的信息
        assert(next_loaded <= iter->first);
        if (iter->first == next_loaded) {
            const size_t write_num = _output.write(iter->second);
            next_loaded += write_num;
            // 如果没写全，则说明写满了，保留剩余没写全的部分并退出
            if (write_num < iter->second.size()) {
                string_len += iter->second.size() - write_num;
                str_map.insert(make_pair(next_loaded, std::move(iter->second.substr(write_num))));

                string_len -= iter->second.size();
                str_map.erase(iter);
                break;
            }
            // 如果写全了，则删除原有迭代器，并进行更新
            string_len -= iter->second.size();
            iter = str_map.erase(iter);
        }
        // 否则直接离开
        else
            break;
    }
    if (eof)
        _eof_idx = index + data.size();
    if (_eof_idx <= next_loaded)
        _output.end_input();
}

size_t StreamReassembler::unassembled_bytes() const { return string_len; }

bool StreamReassembler::empty() const { return string_len == 0; }
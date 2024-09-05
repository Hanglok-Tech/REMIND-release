#pragma once
#include <vector>
#include <iostream>
#include <cstring>
 
class CByteArray {
private:
    std::vector<char> data;
 
public:
    ~CByteArray() {}
    CByteArray() {}
    CByteArray(const char *str) {
        if (str) {
            data.assign(str, str + std::strlen(str));
        }
    }
 
    // 添加数据
    void append(const char *str) {
        data.insert(data.end(), str, str + std::strlen(str));
    }

    void append(const char *str, int len) {
        data.insert(data.end(), str, str + len);
    }

    void append(const unsigned char *str, int len) {
        data.insert(data.end(), str, str + len);
    }

    void append(const unsigned char c) {
        data.push_back(c);
    }
 
    char at(uint64_t index) {
        if (index >= data.size()) {
            return 0;
        }
        return data.at(index);
    }

    // 获取数据
    const char *datas() const {
        return data.data();
    }

    char *pdata() {
        return &data[0];
    }
 
    // 获取大小
    size_t size() const {
        return data.size();
    }

    size_t length() const {
        return data.size();
    }
 
    // 清空数据
    void clear() {
        data.clear();
    }

    void appendUInt32(uint32_t v){
        append(uint8_t((0xff000000&v)>>24));
        append(uint8_t((0x00ff0000&v)>>16));
        append(uint8_t((0x0000ff00&v)>>8));
        append(uint8_t( 0x000000ff&v));
    }

    void appendUInt64(uint64_t v){
        append(uint8_t((0xff00000000000000&v)>>56));
        append(uint8_t((0x00ff000000000000&v)>>48));
        append(uint8_t((0x0000ff0000000000&v)>>40));
        append(uint8_t((0x000000ff00000000&v)>>32));
        append(uint8_t((0x00000000ff000000&v)>>24));
        append(uint8_t((0x0000000000ff0000&v)>>16));
        append(uint8_t((0x000000000000ff00&v)>>8));
        append(uint8_t( 0x00000000000000ff&v));
    }
};

#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <memory>

using namespace std;

class PackageStream {
public:
    PackageStream(std::string data, int32_t package_len): package_len_(package_len), data_(data) {}

    int32_t PackageLen() const {
        return package_len_;
    }

    int32_t ReadPackage(char* buf) {
        int32_t next_pos = min<int32_t>(data_.size(),  pos_ + PackageLen());
        int32_t len = next_pos - pos_;

        memcpy(buf, data_.c_str() + pos_, len);
        pos_ = next_pos;
        return len;
    }

private:
    const int32_t package_len_;
    int32_t pos_ = 0;

    std::string data_;
};

class BufferedReader {
public:
    explicit BufferedReader(PackageStream* stream){
        this->stream = stream;
        buf_read = new char[stream->PackageLen()];
        pos = stream->PackageLen();
    }

    int32_t Read(char* output_buffer, int32_t buffer_len) {
        int count = 0; // кол-во записанного в буфер
        int quan = 0; // сколько мы должны записать на тек. шаге

        while (buffer_len != count) {
            if (pos == stream->PackageLen()) {
                pos = 0;
                count_buf = stream->ReadPackage(buf_read);
            }
            quan = min<int32_t >(buffer_len - count, count_buf - pos);
            memcpy(output_buffer + count, buf_read + pos, quan);
            count += quan;
            pos += quan;
            if (count_buf < stream->PackageLen()) {
                break;
            }
        }
        return count;
    }

    ~BufferedReader(){
        delete [] buf_read;
    }

private:
    PackageStream* stream;
    char* buf_read;
    int pos;
    int count_buf = 0; // кол-во записанного через ридпак
};

int main() {
    int32_t package_len = 0;
    int32_t read_len = 0;
    int32_t expect_len = 0;
    int ok = true;
    int cur_byte = 0;

    cin >> package_len;
    string s;
    getline(cin, s);
    getline(cin, s);
    PackageStream stream(s, package_len);
    BufferedReader reader(&stream);

    while (cin >> read_len >> expect_len) {
        std::unique_ptr<char[]> buf(new char[read_len]);

        int got_len = reader.Read(buf.get(), read_len);
        if (got_len != expect_len || memcmp(buf.get(), s.c_str() + cur_byte, expect_len) != 0) {
            ok = false;
            break;
        }

        cur_byte += read_len;
    }

    cout << (int)ok << endl;
}
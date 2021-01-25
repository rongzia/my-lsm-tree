//
// Created by rrzhang on 19-2-22.
//

#include <iostream>
#include <fcntl.h>
#include <cassert>
#include <cstring>
//#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>

int main(){


        char * mapping = nullptr;
        int mapping_length = 10;

        int mapping_fd = open("/home/rrzhang/Documents/test.txt".c_str(), O_RDWR | O_CREAT | O_TRUNC, 0600);
        assert(mapping_fd != -1);

        // Set the file to the appropriate length
        int result = lseek(mapping_fd, mapping_length - 1, SEEK_SET);
        assert(result != -1);
        result = write(mapping_fd, "", 1);
        assert(result != -1);

        mapping = (char *)mmap(0, mapping_length, PROT_WRITE, MAP_SHARED, mapping_fd, 0);
        assert(mapping != MAP_FAILED);


    return 0;
}
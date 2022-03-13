#define FUSE_USE_VERSION 30
#include <fuse.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

static void fill_stat(const char*path, struct stat *st) {
    st->st_uid = getuid();
    st->st_gid = getgid();
    st->st_atime = time(NULL);
    st->st_mtime = time(NULL);

    if (strcmp(path, "/") == 0) {
        st->st_mode = S_IFDIR | 0755;
        st->st_nlink = 2;
    } else {
        st->st_mode = S_IFREG | 0644;
        st->st_nlink = 1;
        st->st_size = 1024;
    }
}

static int do_getattr(const char *path, struct stat *st, struct fuse_file_info *fi) {
    (void) fi;
    fill_stat(path, st);
    return 0;
}

static int do_readdir(const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi, enum fuse_readdir_flags flag) {
    (void) offset;
    (void) fi;
    (void) flag;
    
    struct stat st;
    fill_stat(path, &st);
    filler(buffer, ".", &st, 0, 0);
    if (strcmp(path, "/") == 0) {
        filler(buffer, "file54", &st, 0, 0);
        filler(buffer, "file349", &st, 0, 0);
    }
    return 0;
}

static int do_read(const char *path, char *buffer, size_t size, off_t offset, struct fuse_file_info *fi) {
    char file54Text[] = "Hello world from File54!";
    char file349Text[] = "Hello world from File349!";
    char *selectedText = NULL;

    if (strcmp(path, "/file54") == 0) selectedText = file54Text;
    else if (strcmp(path, "/file349") == 0) selectedText = file349Text;
    else return -1;
    
    memcpy(buffer, selectedText + offset, size);
    return strlen(selectedText) - offset;
}


static struct fuse_operations operations = {
    .getattr        =       do_getattr,
    .readdir        =       do_readdir,
    .read           =       do_read,
};

int main(int argc, char *argv[]) {
    return fuse_main(argc, argv, &operations, NULL);
}


#include <stdio.h>
#include <ft_nm.h>
#include <string.h>

flag_t flags;
int n_files;

void *map_file(char *filepath, struct stat *st) {
    int fd = open(filepath, O_RDONLY);
    if (fd == -1) {
		ft_fprintf(2, "ft_nm: '%s': No such file\n", filepath);
        return NULL;
    }

    if (fstat(fd, st) == -1) {
        perror("Error getting file size");
        close(fd);
        return NULL;
    }

    void *addr = mmap(NULL, st->st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (addr == MAP_FAILED) {
        perror("Error mapping file");
        close(fd);
        return NULL;
    }
    
    close(fd);
    return addr;
}

void parse_args(char **arg)
{
	while (*arg) {
		if (*arg[0] == '-') {
			if (!ft_strcmp(*arg, "-a") || !ft_strcmp(*arg, "--debug-syms")) {
				flags.a = 1;
			} else if (!ft_strcmp(*arg, "-g") || !ft_strcmp(*arg, "--extern-only")) {
				flags.g = 1;
			} else if (!ft_strcmp(*arg, "-u") || !ft_strcmp(*arg, "--undefined-only")) {
				flags.u = 1;
			} else if (!ft_strcmp(*arg, "-r") || !ft_strcmp(*arg, "--reverse-sort")) {
				flags.r = 1;
			} else if (!ft_strcmp(*arg, "-p") || !ft_strcmp(*arg, "--no-sort")) {
				flags.p = 1;
			}
		}
		arg++;
	}
}

int main(int argc, char *argv[])
{
	parse_args(argv);

	int status = 0;
	int i = 1;

	while (i < argc) {
		if (argv[i] && argv[i][0] != '-') {
			n_files++;
		}
		i++;
	}
	i = 1;
	if (n_files) {
		while (i < argc) {
			if (argv[i] && argv[i][0] != '-') {
				struct stat st;
				void *mapped_file = map_file(argv[i], &st);
				if (!mapped_file) return 1;
				status = ft_nm(mapped_file, st, argv[i]);
				munmap(mapped_file, st.st_size);
			}
			i++;
		}
	} else {
		struct stat st;
		void *mapped_file = map_file("a.out", &st);
		if (!mapped_file) return 1;
		status = ft_nm(mapped_file, st, "a.out");
		munmap(mapped_file, st.st_size);
	}

	return status;
}

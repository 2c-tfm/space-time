#include <space_time.h>

char *read_file(const char *path) {
	FILE *fp = fopen(path, "rb");

	if (!fp)
		return NULL;

	if (fseek(fp, 0, SEEK_END) != 0)
		return NULL;
	long size = ftell(fp);
	if (size < 0)
		return NULL;
	rewind(fp);

	char *buffer = MemAlloc((size_t)size + 1);
	size_t bytes_read = fread(buffer, 1, (size_t)size, fp);
	fclose(fp);

	if (bytes_read != (size_t)size) {
		free(buffer);
		return NULL;
	}
	buffer[size] = '\0';
	return buffer;
}

int main(int argc, char **argv){
	if (argc < 2){
		puts("no space configuration file is given, exiting");
		exit(EXIT_FAILURE);
	}
	char *cfg = read_file(argv[1]);
	if (cfg == NULL){
		puts("cannot read config file, exiting");
		exit(EXIT_FAILURE);
	}
	// initializing the console
	memset(&cons.cline, 0, MAX_LINE);
	memset(&cons.log, 0, MAX_LINE * MAX_LOG);

	init_space_objects(cfg);

	InitWindow(WIN_X, WIN_Y, WIN_NAME);
	SetTargetFPS(60);

	SetExitKey(KEY_NULL);
	theta = atan(1/sqrt(2));

	render_frame();
	return (0);
}

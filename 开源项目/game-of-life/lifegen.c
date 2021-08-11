#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>

#define FATAL(s)                                                  \
    do {                                                          \
        fprintf(stderr, "%s: " s " -- %s\n", argv[0], optarg);    \
        exit(EXIT_FAILURE);                                       \
    } while (0);

struct config {
    unsigned width;
    unsigned height;
    double delay;
    const char *makefile;
    const char *rules;
    char alive;
    char dead;
};

static unsigned
cell_width(unsigned x)
{
    unsigned result = 1;
    unsigned value = 10;
    while (value <= x) {
        value *= 10;
        result++;
    }
    return result;
}

static void
cell_name(char *dst, const struct config *c, unsigned x, unsigned y)
{
    unsigned wx = cell_width(c->width);
    unsigned wy = cell_width(c->width);
    sprintf(dst, "%0*u%0*u", wx, x, wy, y);
}

static bool
rule_eval(const char *rules, unsigned count, bool state)
{
    size_t length = strlen(rules);
    for (const char *p = rules + length - 1; p >= rules && *p != '/'; p--)
        if ((unsigned)*p == count + '0')
            return true;
    for (const char *p = rules; p < rules + length && *p != '/'; p++)
        if ((unsigned)*p == count + '0')
            return state;
    return false;
}

static void
print_target(const struct config *c)
{
    printf("output :\n");
    printf("\t@printf \"$(output)\"\n");
    if (c->delay != 0.0)
        printf("\t@sleep %f\n", c->delay);
    printf("\t@$(MAKE) -f %s $(args)\n", c->makefile);
}

static void
print_rules(const struct config *c)
{
    for (unsigned n = 0; n < 512; n++) {
        char lvalue[10];
        unsigned count = 0;
        for (unsigned i = 0; i < 9; i++) {
            unsigned set = (n >> i) & 1;
            if (i != 4) // !self
                count += set;
            lvalue[i] = set ? c->alive : c->dead;
        }
        lvalue[9] = 0;
        bool state = ((n >> 4) & 1) == 1;
        bool result = rule_eval(c->rules, count, state);
        printf("%s = %c\n", lvalue, result ? c->alive : c->dead);
    }
}

static void
print_init(const struct config *c)
{
    for (unsigned y = 0; y < c->height; y++)
        for (unsigned x = 0; x < c->width; x++) {
            char cell[64];
            cell_name(cell, c, x, y);
            double v = rand() / (double)RAND_MAX;
            printf("%s = %c\n", cell, v < 0.5 ? c->alive : c->dead);
        }
}

static void
print_compute(const struct config *c)
{
    for (unsigned y = 0; y < c->height; y++)
        for (unsigned x = 0; x < c->width; x++) {
            char cell[64];
            cell_name(cell, c, x, y);
            printf("n%s = $(", cell);
            for (int dy = -1; dy <= 1; dy++)
                for (int dx = -1; dx <= 1; dx++) {
                    char source[64];
                    unsigned xx = (x + dx + c->width)  % c->width;
                    unsigned yy = (y + dy + c->height) % c->height;
                    cell_name(source, c, xx, yy);
                    printf("$(%s)", source);
                }
            puts(")");
        }
}

static void
print_output(const struct config *c)
{
    printf("output = \\033[2J\\033[H");
    for (unsigned y = 0; y < c->height; y++) {
        for (unsigned x = 0; x < c->width; x++) {
            char cell[64];
            cell_name(cell, c, x, y);
            printf("$(%s)", cell);
        }
        printf("\\n");
    }
    puts("");
}

static void
print_args(const struct config *c)
{
    printf("args =");
    for (unsigned y = 0; y < c->height; y++)
        for (unsigned x = 0; x < c->width; x++) {
            char cell[64];
            cell_name(cell, c, x, y);
            printf(" %s=$(n%s)", cell, cell);
        }
    puts("");
}

static void
print_help(FILE *o, const char *progname)
{
    fprintf(o, "usage: %s [options]\n", progname);
    fprintf(o, "  -c <cellspec>      pair of alive/dead characters (@.)\n");
    fprintf(o, "  -d <delay>         fractional delay between frames (0.1)\n");
    fprintf(o, "  -f <filename>      internal makefile name (life.mak)\n");
    fprintf(o, "  -h                 print this help information\n");
    fprintf(o, "  -r <rules>         games of life rules (23/3)\n");
    fprintf(o, "  -s <seed>          initialization seed\n");
    fprintf(o, "  -z <width:height>  grid size in characters (50:40)\n");
}

int
main(int argc, char **argv)
{
    struct config config = {
        .width = 50,
        .height = 40,
        .delay = 0.1,
        .makefile = "life.mak",
        .rules = "23/3",
        .alive = '@',
        .dead = '.',
    };

    int option;
    while ((option = getopt(argc, argv, "c:d:f:hr:s:z:")) != -1) {
        switch (option) {
            case 'c': {
                char a = config.alive = optarg[0];
                char d = config.dead = optarg[1];
                const char *verboten = " \t\n\v\f\r=:&%()";
                if (strchr(verboten, a) || strchr(verboten, d))
                    FATAL("invalid cell spec");
            } break;
            case 'd': {
                config.delay = strtod(optarg, NULL);
                if (config.delay < 0)
                    FATAL("invalid delay");
            } break;
            case 'f': {
                for (char *p = optarg; *p; p++)
                    if (isspace(*p))
                        FATAL("invalid filename");
                config.makefile = optarg;
            } break;
            case 'h': {
                print_help(stdout, argv[0]);
                exit(EXIT_SUCCESS);
            } break;
            case 'r': {
                unsigned d;
                config.rules = optarg;
                if (sscanf(config.rules, "%u/%u", &d, &d) != 2)
                    FATAL("invalid rules");
            } break;
            case 's': {
                srand(atoi(optarg));
            } break;
            case 'z': {
                int r = sscanf(optarg, "%u:%u", &config.width, &config.height);
                if (r != 2)
                    FATAL("invalid size");
            } break;
            default: {
                char message[2] = {option};
                optarg = message;
                print_help(stderr, argv[0]);
                exit(EXIT_FAILURE);
            } break;
        }
    }

    print_target(&config);
    puts("");
    print_rules(&config);
    puts("");
    print_init(&config);
    puts("");
    print_compute(&config);
    puts("");
    print_output(&config);
    puts("");
    print_args(&config);

    return 0;
}

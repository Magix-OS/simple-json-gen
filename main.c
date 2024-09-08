#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <jansson.h>
char buffer[1024];
void add_disk(json_t *layout, const char *path, const char *mount, const char *filesystem, const int wipe) {
    json_t *disk = json_object();
    json_t *args = json_object();
    json_object_set(disk, "path", json_string(path));
    json_object_set(args, "mount",json_string(mount));
    json_object_set(args, "filesystem",json_string(filesystem));
    json_object_set(args, "wipe",json_boolean(wipe));
    json_object_set(disk, "args", args);
    json_array_append(layout, disk);
}
int y_n_question() {
    char c;
    scanf(" %c", &c);
    if(tolower(c) == 'y' || c == '1')
        return 1;
    return 0;
}
void get_input(char *input) {
    int length;
    *input = '\0';
    do {
        if (fgets(buffer, 1024, stdin) == NULL) {
            break;
        }
        length = strlen(buffer)-1;
        buffer[length] = '\0';
    } while (length == 0);
}
int main(void) {
    json_t *root = json_object();
    json_t *layout = json_array();
    json_t *config = json_object();
    json_t *locales = json_array();
    json_t *filesystems = json_array();
    json_t *stratas = json_array();
    json_object_set(root, "layout", layout);
    int repeat = 0;
    do {
        char pathbuf[1024];
        char mountbuf[1024];
        char fsbuf[1024];
        printf("Insert the path to your partition: \n");
        scanf("%s", &pathbuf);
        printf("Insert the mountpoint of this partition: \n");
        scanf("%s", &mountbuf);
        printf("Insert the filesystem of this partition: \n");
        scanf("%s", &fsbuf);
        printf("Would you like to wipe it ? [Y/N] \n");
            int wipe = y_n_question();
        add_disk(layout,pathbuf,mountbuf,fsbuf, wipe);
        printf("Want to add another partition ? [Y/N]\n");
            repeat = y_n_question();


    } while (repeat);

    json_object_set(root, "config", config);
    printf("Bedrock Integration ?: \n");
    json_object_set(config, "bedrock", json_boolean(y_n_question()));
    printf("Flatpak Integration ?: \n");
    json_object_set(config, "flatpak", json_boolean(y_n_question()));
    printf("SystemD ?: \n");
    json_object_set(config, "init", json_boolean(y_n_question()));
    printf("Intel micrcode ?: \n");
    json_object_set(config, "intel_microcode", json_boolean(y_n_question()));
    printf("Binary Kernel ?: \n");
    json_object_set(config, "kernel", json_boolean(y_n_question()));
    printf("Linux Firmware ?: \n");
    json_object_set(config, "linux_firmware", json_boolean(y_n_question()));
    printf("Disable binhost ?: \n");
    json_object_set(config, "portage", json_boolean(y_n_question()));
    printf("Use Doas ?: \n");
    json_object_set(config, "priv_escal", json_boolean(y_n_question()));
    printf("Sof Firmware ?: \n");
    json_object_set(config, "sof_firmware", json_boolean(y_n_question()));
    printf("World update ?: \n");
    json_object_set(config, "world_update", json_boolean(y_n_question()));
    printf("Input a SPACE if you want to leave empty from now on : \n");
    printf("Enter the path to the stage4 : \n");
    get_input(buffer);
    json_object_set(config, "filename", json_string(buffer));
    printf("Enter your GPUs: \n");
    get_input(buffer);
    json_object_set(config, "gpus", json_string(buffer));
    printf("Select your boot disk: \n");
    get_input(buffer);
    json_object_set(config, "grub_disk", json_string(buffer));
    printf("Select your hostname: \n");
    get_input(buffer);
    json_object_set(config, "hostname", json_string(buffer));
    printf("Keyboard layout: \n");
    get_input(buffer);
    json_object_set(config, "keyboard", json_string(buffer));
    printf("Primary Locale: \n");
    get_input(buffer);
    json_object_set(config, "locale", json_string(buffer));
    json_array_append(locales,json_string(buffer));
    printf("Want to add another locale ? [Y/N]\n");
    repeat = y_n_question();
    while(repeat) {
        printf("Insert a locale: \n");
        get_input(buffer);
        json_array_append(locales,json_string(buffer));
        printf("Want to add another locale ? [Y/N]\n");
        repeat = y_n_question();
    }
    printf("Additional Packages: \n");
    get_input(buffer);
    json_object_set(config, "packages", json_string(buffer));
    printf("User password: \n");
    get_input(buffer);
    json_object_set(config, "passwd", json_string(buffer));
    printf("Root password: \n");
    get_input(buffer);
    json_object_set(config, "rootpasswd", json_string(buffer));
    printf("Timezone: \n");
    get_input(buffer);
    json_object_set(config, "timezone", json_string(buffer));
    printf("Custom Useflags: \n");
    get_input(buffer);
    json_object_set(config, "useflags", json_string(buffer));
    printf("Username: \n");
    get_input(buffer);
    json_object_set(config, "username", json_string(buffer));
    json_object_set(config, "locales", locales);
    json_object_set(config, "stratas", stratas);
    json_object_set(config, "filesystems", filesystems);
    printf("Arch strata ?: \n");
    json_array_append(stratas, json_boolean(y_n_question()));
    printf("Debian strata ?: \n");
    json_array_append(stratas, json_boolean(y_n_question()));
    printf("Fedora strata ?: \n");
    json_array_append(stratas, json_boolean(y_n_question()));
    printf("Ubuntu strata ?: \n");
    json_array_append(stratas, json_boolean(y_n_question()));
    printf("Void strata ?: \n");
    json_array_append(stratas, json_boolean(y_n_question()));
    printf("XFS support ?: \n");
    json_array_append(filesystems, json_boolean(y_n_question()));
    printf("EXT4 support ?: \n");
    json_array_append(filesystems, json_boolean(y_n_question()));
    printf("VFAT support ?: \n");
    json_array_append(filesystems, json_boolean(y_n_question()));
    printf("BTRFS support ?: \n");
    json_array_append(filesystems, json_boolean(y_n_question()));
    printf("ZFS support ?: \n");
    json_array_append(filesystems, json_boolean(y_n_question()));
    printf("JFS support ?: \n");
    json_array_append(filesystems, json_boolean(y_n_question()));

    char *s = json_dumps(root, 0);
    puts(s);
    json_decref(root);

    return 0;
}
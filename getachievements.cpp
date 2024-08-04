#include "getachievements.h"
#include "cJSON.h"
#include "stdio.h"
#include <cstring>
#include <QDebug>

GetAchievements::GetAchievements(char* achiName) {

    FILE *fp = fopen("Achievements.json", "r");
    if (fp == NULL) {
        qDebug("Error: Unable to open the file.\n");
        return;
    }

    char buffer[1024] = {0};
    size_t len = fread(buffer, 1, sizeof(buffer) - 1, fp);
    fclose(fp);

    // parse the JSON data
    cJSON *json = cJSON_Parse(buffer);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            qDebug("Error: %s\n", error_ptr);
        }
        return;
    }

    cJSON *name = cJSON_GetObjectItemCaseSensitive(json, "Name");
    if (cJSON_IsString(name) && (name->valuestring != NULL)) {
        qDebug("Name: %s\n", name->valuestring);
        strncpy(achiName, name->valuestring, 255);
        achiName[255] = '\0';
    }

    // delete the JSON object
    cJSON_Delete(json);

}

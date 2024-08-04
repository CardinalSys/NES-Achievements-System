#include "getachievements.h"
#include "cJSON.h"
#include "stdio.h"
#include <cstring>
#include <QDebug>

GetAchievements::GetAchievements(std::list<Achievement>& achievementList) {

    FILE *fp = fopen("Achievements.json", "r");
    if (fp == NULL) {
        qDebug("Error: Unable to open the file.\n");
        return;
    }

    char buffer[4096] = {0};
    size_t len = fread(buffer, 1, sizeof(buffer) - 1, fp);
    fclose(fp);

    if (len == 0) {
        qDebug("Error: Empty file.\n");
        return;
    }

    qDebug("JSON content: %s", buffer);

    cJSON *json = cJSON_Parse(buffer);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            qDebug("Error: %s\n", error_ptr);
        }
        return;
    }

    if (!cJSON_IsArray(json)) {
        qDebug("Error: JSON is not an array.\n");
        cJSON_Delete(json);
        return;
    }


    cJSON *achievement = NULL;
    cJSON_ArrayForEach(achievement, json) {

        if (!cJSON_IsObject(achievement)) {
            continue; // Skip non-object items
        }

        Achievement a;
        a.gameId = cJSON_GetObjectItemCaseSensitive(achievement, "GameId")->valueint;
        a.id = cJSON_GetObjectItemCaseSensitive(achievement, "Id")->valueint;

        cJSON *name = cJSON_GetObjectItemCaseSensitive(achievement, "Name");
        if (cJSON_IsString(name) && (name->valuestring != NULL)) {
            a.name = name->valuestring;
        }

        cJSON *description = cJSON_GetObjectItemCaseSensitive(achievement, "Description");
        if (cJSON_IsString(description) && (description->valuestring != NULL)) {
            a.description = description->valuestring;
        }

        cJSON *aob = cJSON_GetObjectItemCaseSensitive(achievement, "AoB");
        if (cJSON_IsString(aob) && (aob->valuestring != NULL)) {
            a.aob = aob->valuestring;
        }

        a.value = cJSON_GetObjectItemCaseSensitive(achievement, "Value")->valueint;
        a.obtained = cJSON_GetObjectItemCaseSensitive(achievement, "Obtained")->valueint;

        achievementList.push_back(a);
    }

    cJSON_Delete(json);
}

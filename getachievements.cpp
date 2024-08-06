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

    cJSON *game = NULL;
    cJSON_ArrayForEach(game, json) {
        if (!cJSON_IsObject(game)) {
            continue;
        }

        cJSON *achievementsArray = cJSON_GetObjectItemCaseSensitive(game, "Achievements");
        if (!cJSON_IsArray(achievementsArray)) {
            qDebug("Error: Achievements is not an array.\n");
            continue;
        }

        cJSON *achievement = NULL;
        cJSON_ArrayForEach(achievement, achievementsArray) {
            if (!cJSON_IsObject(achievement)) {
                continue;
            }

            Achievement a;
            a.gameId = cJSON_GetObjectItemCaseSensitive(game, "GameId")->valueint;

            cJSON *id = cJSON_GetObjectItemCaseSensitive(achievement, "Id");
            if (cJSON_IsNumber(id)) {
                a.id = id->valueint;
            }

            cJSON *name = cJSON_GetObjectItemCaseSensitive(achievement, "Name");
            if (cJSON_IsString(name) && (name->valuestring != NULL)) {
                a.name = name->valuestring;
            }

            cJSON *description = cJSON_GetObjectItemCaseSensitive(achievement, "Description");
            if (cJSON_IsString(description) && (description->valuestring != NULL)) {
                a.description = description->valuestring;
            }

            cJSON *url = cJSON_GetObjectItemCaseSensitive(achievement, "Url");
            if (cJSON_IsString(url) && (url->valuestring != NULL)) {
                a.url = url->valuestring;
            }

            cJSON *offset = cJSON_GetObjectItemCaseSensitive(achievement, "Offset");
            if (cJSON_IsString(offset) && (offset->valuestring != NULL)) {
                a.offset = offset->valuestring;
            }

            cJSON *value = cJSON_GetObjectItemCaseSensitive(achievement, "Value");
            if (cJSON_IsNumber(value)) {
                a.value = value->valueint;
            }

            cJSON *obtained = cJSON_GetObjectItemCaseSensitive(achievement, "Obtained");
            if (cJSON_IsNumber(obtained)) {
                a.obtained = obtained->valueint;
            }

            achievementList.push_back(a);
        }
    }

    cJSON_Delete(json);
}

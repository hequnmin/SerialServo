#include "Command.hpp"

namespace ATE 
{
    Command::Command(/* args */)
    {
    }

    Command::~Command()
    {
    }

    bool Command::parseBasic(const char *json, REQUEST_BODY_BASIC *basic) {

        cJSON *doc, *id, *cmd;
        doc = cJSON_Parse(json);
        if (doc == NULL) {
            const char *jsonError = cJSON_GetErrorPtr();
            if (jsonError && *jsonError != '\0' ) {
                basic->err = jsonError;
            } else {
                basic->err = "json error.";
            }
            return false;

        } else {
            id = cJSON_GetObjectItem(doc, "id");
            if (id == NULL) {
                basic->err = "id error.";
                return false;
            }

            cmd = cJSON_GetObjectItem(doc, "cmd");
            if (cmd == NULL) {
                basic->err = "cmd error.";
                return false;
            }

            basic->id = id->valueint;
            basic->cmd = cmd->valuestring;

            if (strcmp(basic->cmd, "info") == 0) {
                basic->key = REQUEST_KEY::REQUEST_KEY_INFO;
            } else if (strcmp(basic->cmd, "reset") == 0) {
                basic->key = REQUEST_KEY::REQUEST_KEY_RESET;
            } else {
                basic->key = REQUEST_KEY::REQUEST_KEY_ERROR;
                basic->err = "cmd invalid.";
                return false;
            }

        }
        return true;
    }

    bool Command::parseInfo(const char* json, REQUEST_BODY_INFO* info) {

        cJSON *doc, *id, *cmd;
        doc = cJSON_Parse(json);
        if (doc == NULL) {
            return info;
        } else {

            id = cJSON_GetObjectItem(doc, "id");
            cmd = cJSON_GetObjectItem(doc, "cmd");

            info->id = id->valueint;
            info->cmd = cmd->valuestring;

            if (strcmp(info->cmd, "info") == 0) {
                info->key = REQUEST_KEY::REQUEST_KEY_INFO;
            } else {
                info->err = "cmd error.";
                return false;
            }
        }
        return info;
    }

    bool Command::parseReset(const char* json, REQUEST_BODY_RESET* reset) {

        cJSON *doc, *id, *cmd;
        doc = cJSON_Parse(json);
        if (doc == NULL) {
            return false;
        } else {

            id = cJSON_GetObjectItem(doc, "id");
            cmd = cJSON_GetObjectItem(doc, "cmd");

            reset->id = id->valueint;
            reset->cmd = cmd->valuestring;

            if (strcmp(reset->cmd, "reset") == 0) {
                reset->key = REQUEST_KEY::REQUEST_KEY_RESET;
            } else {
                reset->key = REQUEST_KEY::REQUEST_KEY_ERROR;
                reset->err = (char*)"cmd error.";
                return false;
            }

        }
        return true;
    }

    char* Command::printBasic(RESPONSE_BODY_BASIC* resBasic) {
        cJSON *doc = cJSON_CreateObject();
        
        cJSON_AddItemToObject(doc, "id", cJSON_CreateNumber(resBasic->id));
        cJSON_AddItemToObject(doc, "err", cJSON_CreateString(resBasic->err));

        return cJSON_Print(doc);
    }

    char* Command::printInfo(RESPONSE_BODY_INFO* resInfo) {
        cJSON *doc = cJSON_CreateObject();
        
        cJSON_AddItemToObject(doc, "id", cJSON_CreateNumber(resInfo->id));
        cJSON_AddItemToObject(doc, "err", cJSON_CreateString(resInfo->err));

        cJSON_AddItemToObject(doc, "mac", cJSON_CreateString(resInfo->mac));
        cJSON_AddItemToObject(doc, "ver", cJSON_CreateString(resInfo->ver));
        cJSON_AddItemToObject(doc, "chi", cJSON_CreateString(resInfo->chi));

        cJSON_AddItemToObject(doc, "chn", cJSON_CreateNumber(resInfo->chn));
        cJSON_AddItemToObject(doc, "cnn", cJSON_CreateNumber(resInfo->cnn));


        return cJSON_Print(doc);
    }

    char* Command::printReset(RESPONSE_BODY_RESET* resReset) {
        cJSON *doc = cJSON_CreateObject();
        
        cJSON_AddItemToObject(doc, "id", cJSON_CreateNumber(resReset->id));
        cJSON_AddItemToObject(doc, "err", cJSON_CreateString(resReset->err));

        return cJSON_Print(doc);
    }

}

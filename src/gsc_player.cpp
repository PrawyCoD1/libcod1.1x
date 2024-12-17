#include "shared.hpp"

extern cvar_t *player_sprintTime;

void gsc_player_setvelocity(scr_entref_t ref)
{
    int id = ref.entnum;
    vec3_t velocity;

    if (!stackGetParams("v", &velocity))
    {
        stackError("gsc_player_setvelocity() argument is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_setvelocity() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    playerState_t *ps = SV_GameClientNum(id);
    VectorCopy(velocity, ps->velocity);

    stackPushBool(qtrue);
}

void gsc_player_getvelocity(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_getvelocity() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    playerState_t *ps = SV_GameClientNum(id);

    stackPushVector(ps->velocity);
}

void gsc_player_getuserinfo(scr_entref_t ref)
{
    int id = ref.entnum;
    char *key;

    if (!stackGetParams("s", &key))
    {
        stackError("gsc_player_getuserinfo() argument is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_getuserinfo() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];
    char *val = Info_ValueForKey(client->userinfo, key);

    if (strlen(val))
        stackPushString(val);
    else
        stackPushString("");
}

void gsc_player_setuserinfo(scr_entref_t ref)
{
    int id = ref.entnum;
    char *key, *value;

    if (!stackGetParams("ss", &key, &value))
    {
        stackError("gsc_player_setuserinfo() one or more arguments is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_setuserinfo() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];
    Info_SetValueForKey(client->userinfo, key, value);

    stackPushBool(qtrue);
}

void gsc_player_button_ads(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_button_ads() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    stackPushBool(client->lastUsercmd.buttons & KEY_MASK_ADS_MODE ? qtrue : qfalse);
}

void gsc_player_button_left(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_button_left() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    stackPushBool(client->lastUsercmd.rightmove == KEY_MASK_MOVELEFT ? qtrue : qfalse);
}

void gsc_player_button_right(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_button_right() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    stackPushBool(client->lastUsercmd.rightmove == KEY_MASK_MOVERIGHT ? qtrue : qfalse);
}

void gsc_player_button_forward(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_button_forward() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    stackPushBool(client->lastUsercmd.forwardmove == KEY_MASK_FORWARD ? qtrue : qfalse);
}

void gsc_player_button_back(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_button_back() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    stackPushBool(client->lastUsercmd.forwardmove == KEY_MASK_BACK ? qtrue : qfalse);
}

void gsc_player_button_jump(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_button_jump() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    stackPushBool(client->lastUsercmd.upmove == KEY_MASK_JUMP ? qtrue : qfalse);
}

void gsc_player_button_leanleft(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_button_leanleft() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];
    
    stackPushBool(client->lastUsercmd.wbuttons & KEY_MASK_LEANLEFT ? qtrue : qfalse);
}

void gsc_player_button_leanright(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_button_leanright() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    stackPushBool(client->lastUsercmd.wbuttons & KEY_MASK_LEANRIGHT ? qtrue : qfalse);
}

void gsc_player_button_reload(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_button_reload() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    stackPushBool(client->lastUsercmd.wbuttons & KEY_MASK_RELOAD ? qtrue : qfalse);
}

void gsc_player_getangles(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_getangles() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }
    
    playerState_t *ps = SV_GameClientNum(id);

    stackPushVector(ps->viewangles);
}

void gsc_player_getstance(scr_entref_t ref)
{
    int id = ref.entnum;
    
    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_getstance() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }
    
    playerState_t *ps = SV_GameClientNum(id);
    if(ps->eFlags & EF_CROUCHING)
        stackPushString("crouch");
    else if(ps->eFlags & EF_PRONE)
        stackPushString("prone");
    else
        stackPushString("stand");
}

void gsc_player_getip(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_getip() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];
    char ip[16];
    
    snprintf(ip, sizeof(ip), "%d.%d.%d.%d",
        client->netchan.remoteAddress.ip[0],
        client->netchan.remoteAddress.ip[1],
        client->netchan.remoteAddress.ip[2],
        client->netchan.remoteAddress.ip[3]);

    stackPushString(ip);
}

void gsc_player_getping(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_getping() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];
    stackPushInt(client->ping);
}

void gsc_player_processclientcommand(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_processclientcommand() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    ClientCommand(id);

    stackPushBool(qtrue);
}

void gsc_player_dropclient(scr_entref_t ref)
{
    int id = ref.entnum;
    char *reason;

    if (Scr_GetNumParam() > 0 && !stackGetParams("s", &reason))
    {
        stackError("gsc_player_dropclient() argument has a wrong type");
        stackPushUndefined();
        return;
    }

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_dropclient() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    if(Scr_GetNumParam() > 0)
        SV_DropClient(client, reason);
    else
        SV_DropClient(client, NULL);

    stackPushBool(qtrue);
}

void gsc_player_setspeed(scr_entref_t ref)
{
    int id = ref.entnum;
    int speed;

    if (!stackGetParams("i", &speed))
    {
        stackError("gsc_player_setspeed() argument is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_setspeed() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    if (speed < 0)
    {
        stackError("gsc_player_setspeed() param must be equal or above zero");
        stackPushUndefined();
        return;
    }

    customPlayerState[id].speed = speed;

    stackPushBool(qtrue);
}

void gsc_player_getfps(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_getfps() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    stackPushInt(customPlayerState[id].fps);
}

void gsc_player_isonladder(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_isonladder() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    playerState_t *ps = SV_GameClientNum(id);

    stackPushBool(ps->pm_flags & PMF_LADDER ? qtrue : qfalse);
}

void gsc_player_noclip(scr_entref_t ref)
{
    int id = ref.entnum;
    char *noclip;

    if (!stackGetParams("s", &noclip))
    {
        stackError("gsc_player_noclip() argument is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_noclip() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    gentity_t *entity = &g_entities[id];

    if (!Q_stricmp(noclip, "on") || atoi(noclip))
    {
        entity->client->noclip = qtrue;
    }
    else if (!Q_stricmp(noclip, "off") || !Q_stricmp(noclip, "0"))
    {
        entity->client->noclip = qfalse;
    }
    else
    {
        entity->client->noclip = !entity->client->noclip;
    }

    stackPushBool(qtrue);
}

void gsc_player_ufo(scr_entref_t ref)
{
    int id = ref.entnum;
    char *ufo;

    if (!stackGetParams("s", &ufo))
    {
        stackError("gsc_player_ufo() argument is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_ufo() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    gentity_t *entity = &g_entities[id];

    if (!Q_stricmp(ufo, "on") || atoi(ufo))
    {
        entity->client->ufo = qtrue;
    }
    else if (!Q_stricmp(ufo, "off") || !Q_stricmp(ufo, "0"))
    {
        entity->client->ufo = qfalse;
    }
    else
    {
        entity->client->ufo = !entity->client->ufo;
    }

    stackPushBool(qtrue);
}

void gsc_player_connectionlesspackettoclient(scr_entref_t ref)
{
    int id = ref.entnum;
    char *cmd;

    if (!stackGetParams("s", &cmd))
    {
        stackError("gsc_player_connectionlesspackettoclient() argument is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_connectionlesspackettoclient() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];
    NET_OutOfBandPrint(NS_SERVER, client->netchan.remoteAddress, cmd);

    stackPushBool(qtrue);
}

void gsc_player_setjumpheight(scr_entref_t ref)
{
    int id = ref.entnum;
    float jump_height;

    if (!stackGetParams("f", &jump_height))
    {
        stackError("gsc_player_setjumpheight() argument is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_setjumpheight() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    if(jump_height < 0)
        customPlayerState[id].overrideJumpHeight = false;
    else
    {
        customPlayerState[id].overrideJumpHeight = true;
        customPlayerState[id].jumpHeight = jump_height;
    }

    stackPushBool(qtrue);
}

void gsc_player_setairjumps(scr_entref_t ref)
{
    int id = ref.entnum;
    int airJumps;

    if (!stackGetParams("i", &airJumps))
    {
        stackError("gsc_player_setairjumps() argument is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_setairjumps() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    customPlayerState[id].airJumpsAvailable = airJumps;

    stackPushBool(qtrue);
}

void gsc_player_getairjumps(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_getairjumps() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    stackPushInt(customPlayerState[id].airJumpsAvailable);
}

void gsc_player_disableitemautopickup(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_disableitempickup() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    int old_setting = !customPlayerState[id].noAutoPickup;
    customPlayerState[id].noAutoPickup = true;

    stackPushInt(old_setting);
}

void gsc_player_enableitemautopickup(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_enableitempickup() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    int old_setting = !customPlayerState[id].noAutoPickup;
    customPlayerState[id].noAutoPickup = false;

    stackPushInt(old_setting);
}

void gsc_player_getsprintremaining(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_getsprintremaining() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }
    
    float sprint_time = player_sprintTime->value * 1000.0;
    int timeUsed = customPlayerState[id].sprintTimer;
    int timeRemaining = sprint_time - timeUsed;
    
    stackPushInt(timeRemaining);
}

void gsc_player_playscriptanimation(scr_entref_t ref)
{
    int id = ref.entnum;
    int scriptAnimEventType;
    int isContinue;
    int force;

    if (!stackGetParams("iii", &scriptAnimEventType, &isContinue, &force))
    {
        stackError("gsc_player_playscriptanimation() argument is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_playscriptanimation() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    if (scriptAnimEventType < 0 || scriptAnimEventType >= NUM_ANIM_EVENTTYPES)
    {
        stackError("gsc_player_playscriptanimation() argument is not a valid scriptAnimEventType");
        stackPushUndefined();
        return;
    }
    
    gentity_t *entity = &g_entities[id];

    stackPushInt(BG_AnimScriptEvent(&entity->client->ps, (scriptAnimEventTypes_t)scriptAnimEventType, isContinue, force));
}

void gsc_player_isbot(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_isbot() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    stackPushBool(client->bIsTestClient);
}
void gsc_player_sethiddenfromscoreboard(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_sethiddenfromscoreboard() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    bool hidden = Scr_GetInt(0);
    customPlayerState[id].hiddenFromScoreboard = hidden;

    stackPushBool(true);
}

void gsc_player_ishiddenfromscoreboard(scr_entref_t ref)
{
    int id = ref.entnum;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_ishiddenfromscoreboard() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    stackPushBool(customPlayerState[id].hiddenFromScoreboard);
}

void gsc_player_getuserinfokey(scr_entref_t ref) {
    int id = ref.entnum;
	const char* key = Scr_GetString(0);
	char userinfo[MAX_STRING_CHARS];
	getuserinfo(id, userinfo, sizeof(userinfo));
	
	char* value = Info_ValueForKey(userinfo, key);
	if(value == NULL)
		Scr_AddString("");
	else
		Scr_AddString(value);
}

void gsc_player_freezecontrols(scr_entref_t ref) {
    int id = ref.entnum;
    gentity_t *ent = &g_entities[id];
    qboolean freeze;

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_playscriptanimation() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    freeze = Scr_GetBool(0);

    if (freeze)
        ent->client->ps.pm_flags |= 0x4000;
    else
        ent->client->ps.pm_flags &= ~0x4000;
}

void gsc_player_disableweapon(scr_entref_t ref)
{
    int id = ref.entnum;
	gentity_t *ent = &g_entities[id];
    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_disableweapon() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }
	ent->client->ps.pm_flags |= 0x20000;
}
void gsc_player_enableweapon(scr_entref_t ref)
{
    int id = ref.entnum;
	gentity_t *ent = &g_entities[id];
    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_enableweapon() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }
	ent->client->ps.pm_flags &= ~0x20000;
}

void gsc_player_renamebot(scr_entref_t ref) {
    int id = ref.entnum;
	const char* key = Scr_GetString(0);
	char userinfo[MAX_STRING_CHARS];
	getuserinfo(id, userinfo, sizeof(userinfo));
	
	Info_SetValueForKey(userinfo, "name", key);
	setuserinfo(id, userinfo);
	
	client_t* cl = &svs.clients[id];
	if(cl) {
		memcpy(&cl->name, key, 32);
		cl->name[31] = '\0';
	}
}

void gsc_player_sendservercommand(scr_entref_t ref) {
    int id = ref.entnum;
	const char* cmd = Scr_GetString(0);
	SV_SendServerCommand(&svs.clients[id], 1, cmd);
}

void gsc_player_moveupbuttonpressed(scr_entref_t ref) {
    int id = ref.entnum;
    client_t *cl = &svs.clients[id];
    if(cl) {
        if((cl->lastUsercmd.upmove & 0x7f) == 0x7f) {
            Scr_AddBool(true);
            return;
		}
    }
    Scr_AddBool(false);
}

void gsc_player_movedownbuttonpressed(scr_entref_t ref) {
    int id = ref.entnum;
    client_t *cl = &svs.clients[id];
    if(cl) {
        if((cl->lastUsercmd.upmove & 0x81) == 0x81) {
            Scr_AddBool(true);
            return;
		}
    }
    Scr_AddBool(false);
}

void gsc_player_kickbot(scr_entref_t ref) { //weird playercmd > bot
    int id = ref.entnum;
	client_t* cl = &svs.clients[id];
	if(cl) {
		SV_DropClient(cl, "");
		cl->state = CS_FREE;
	}
}
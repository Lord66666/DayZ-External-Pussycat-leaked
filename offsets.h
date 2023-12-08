#pragma once
#include <Windows.h>

namespace Offsets
{
    uint64_t ADDRESS_WORLD = 0x414A858; //;//  

    uint64_t OFFSET_WORLD_CAMERA = 0x1B8;


    uint64_t OFFSET_CAMERA_VIEWRIGHT = 0x8;
    uint64_t OFFSET_CAMERA_VIEWUP = 0x14;
    uint64_t OFFSET_CAMERA_VIEWFORWARD = 0x20;
    uint64_t OFFSET_CAMERA_VIEWTRANSLATION = 0x2C;
    uint64_t OFFSET_CAMERA_VIEWPORTSIZE = 0x58;
    uint64_t OFFSET_CAMERA_PROJECTION_D1 = 0xD0;
    uint64_t OFFSET_CAMERA_PROJECTION_D2 = 0xDC;


    uint64_t OFFSET_NETWORK_NETWORKMANAGER = 0xEF6EA0;
    uint64_t OFFSET_NETWORK_NETWORKCLIENT = 0x50;//
    uint64_t OFFSET_PLAYERIDENTITY_GUID = 0x38;
    uint64_t OFFSET_NETWORKCLIENT_SERVER = 0x360;
    uint64_t OFFSET_PLAYERIDENTITY_NETWORKID = 0x30;//
    uint64_t OFFSET_PLAYERIDENTITY_PLAYERNAME = 0xF0;
    uint64_t OFFSET_NETWORKCLIENT_PLAYERIDENTITYSIZE = 0x160; //0x158;
    uint64_t OFFSET_NETWORKCLIENT_SCOREBOARD = 0x10;//
    uint64_t OFFSET_SPEEDHACK = 0xE70170;



    uint64_t OFFSET_WORLD_GRASS = 0xB80;
    uint64_t OFFSET_WORLD_RENDERER = 0x28F4;
    uint64_t OFFSET_WORLD_DAY = 0x28F8;

    uint64_t OFFSET_WORLD_CAMERAON = 0x28E8; // 48 8B 81 ? 28 00 00
    uint64_t OFFSET_WORLD_PLAYERON = 0x28E0; //


    uint64_t OFFSET_WORLD_NEARANIMALTABLE = 0xEC8;//
    uint64_t OFFSET_WORLD_FARANIMALTABLE = 0x1010;// 48 8B 92 ? ? ? ? EB 22 
    uint64_t OFFSET_WORLD_SLOWANIMALTABLE = 0x1F90;// 48 8B 8F ? ? ? ? 48 85 C9 74 4A 
    uint64_t OFFSET_WORLD_ITEMTABLE = 0x1FE0;//
    uint64_t OFFSET_WORLD_BULLETTABLE = 0xD80; // 1C8h   48 8D 8F ? ? ? ? E8 ? ? ? ? 48 8D 8F ? ? ? ? E8 ? ? ? ? 48 8D 8F ? ? ? ? E8 ? ? ? ? 48 8D 8F ? ? ? ? E8 ? ? ? ? 48 8D 8F ? ? ? ? E8 ? ? ? ? 48 8D 9F ? ? ? ? 

    uint64_t OFFSET_SORTEDOBJECT_ENTITY = 0x8;
    uint64_t OFFSET_SORTEDOBJECT_ITEM = 0x4;

    uint64_t OFFSET_VISUALSTATE_POSITION = 0x2C;

    uint64_t OFFSET_SKELETON = 0x830; //;//0x760;
    uint64_t OFFSET_ZSKELETON = 0x698;//640 ;

    uint64_t OFFSET_ENTITY_CAMERAENTRY = 0x2188;
    uint64_t OFFSET_ENTITY_FUTUREVISUALSTATE = 0x128;   // 48 8D 90 ? ? ? ? 49 0F 44 D0 48 8B 02  | FutureVisualState | sig: 75 07 48 83 78 ? ? 74 46 
    uint64_t OFFSET_ENTITY_RENDERVISUALSTATE = 0x1D0;  // 48 8B 99 ? ? ? ? 33 C9 | VisualState | 48 83 ED 01 0F 85 ? ? ? ? 44 0F 28 54 24 ?
    uint64_t OFFSET_ENTITY_FUTUREENTITYTYPE = 0x38;
    uint64_t OFFSET_ENTITY_RENDERENTITYTYPE = 0x180; //0x148;
    uint64_t OFFSET_ENTITY_ENTITYDEAD = 0x15D;
    uint64_t OFFSET_ENTITY_SORTOBJECT = 0x190;
    uint64_t OFFSET_ENTITY_BASEENTITY = 0x28B8;
    uint64_t OFFSET_ENTITY_NETWORKID = 0x6FC;//0x69C;// 0x67C; 
    uint64_t OFFSET_ENTITY_INVENTORY = 0x678;
    uint64_t OFFSET_INVENTORY_ITEMINHAND = 0x1B0; // 48 8B 81 ? ? ? ? C3 CC CC CC CC CC CC CC CC 8B C2

    uint64_t OFFSET_ENTITYTYPE_BASETYPE = 0x88;
    uint64_t OFFSET_ENTITYTYPE_TYPENAME = 0x70;
    uint64_t OFFSET_ENTITYTYPE_MODELNAME = 0x80;
    uint64_t OFFSET_ENTITYTYPE_CONFIGNAME = 0xA8;
    uint64_t OFFSET_ENTITYTYPE_CLEANNAME = 0x4E8;

    uint64_t OFFSET_TEXT = 0x10;
    uint64_t OFFSET_LENGTH = 0x8;
    uint64_t OFFSET_AIM = 24;
    uint64_t OFFSET_IS_DEAD = 0xe2;
}
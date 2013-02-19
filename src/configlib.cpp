#include "configlib.h"

#include <iostream>

#include "lua.hpp"

#include "config.h"

namespace Config{

    int config_add_agent( lua_State *L ){
        auto name = luaL_checkstring( L, 1 );
        auto num = luaL_checknumber( L, 2 );
        std::cout << "Creating: " << num << " of " << name << std::endl;
        return 0;
    }

    int config_setvars( lua_State *L ){
        luaL_checktype( L, 1, LUA_TTABLE );
        // push first key
        lua_pushnil( L );
        while( lua_next( L, 1 ) != 0 ) {
            std::string keyname( luaL_checkstring( L, -2 ) );
            std::cout << keyname << " = ";
            auto ltype = lua_type( L, -1 );
            switch( ltype ){
            case LUA_TNUMBER:
                std::cout << lua_tonumber(L, -1 ) << std::endl;
                break;

            case LUA_TSTRING:
                std::cout << "'" << lua_tostring(L, -1 ) << "'" << std::endl;
                break;

            default:
                std::cout << lua_typename(L, ltype ) << std::endl;
            }

            // removes 'value'; keeps 'key' for next iteration
            lua_pop( L, 1 );
        }
        return 0;
    }

    const luaL_Reg configlib[] = {
        {"add_agent",   config_add_agent},
        {"setvars",   config_setvars},
        {nullptr, nullptr}
    };

    int openlib( lua_State *L ){
        // set functions
        luaL_register( L, "config", configlib );
        // Set constants
        lua_pushnumber( L, VERSION_MAJOR );
        lua_setfield( L, -2, "VERSION_MAJOR" );
        lua_pushnumber( L, VERSION_MINOR );
        lua_setfield( L, -2, "VERSION_MINOR" );
        // removes table
        lua_pop( L, 1 );
        return 0;
    }
}

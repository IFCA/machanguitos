/*******************************************************************************
Machanguitos is The Easiest Multi-Agent System in the world. Work done at The
Institute of Physics of Cantabria (IFCA).
Copyright (C) 2013  Luis Cabellos

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/
/** @file configlib.hpp
    @brief Configuration functions.
    @author Luis Cabellos
 */
//------------------------------------------------------------------------------
#ifndef CONFIGLIB_HPP
#define CONFIGLIB_HPP

//------------------------------------------------------------------------------
#include <string>

//------------------------------------------------------------------------------
namespace Config{
    //--------------------------------------------------------------------------
    /** Load a configure file.
        @param filename name of the file to load.
        @ingroup Config
     */
    bool load( const std::string & filename );
}

//------------------------------------------------------------------------------
#endif//CONFIGLIB_HPP

//------------------------------------------------------------------------------

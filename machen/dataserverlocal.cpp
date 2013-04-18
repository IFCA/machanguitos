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
/** @file dataserverlocal.cpp
    @brief Engine::DataServerLocal Definitions.
    @author Luis Cabellos
*/
//------------------------------------------------------------------------------
#include "dataserverlocal.hpp"
#include <cassert>
#include "common/log.hpp"

//------------------------------------------------------------------------------
namespace Engine {
    using namespace std;

    //--------------------------------------------------------------------------
    void DataServerLocal::createRaster( const string & key, int w, int h,
                       double x0, double x1, double y0, double y1 ){
        Util::LOGV( "DataServerLocal::createRaster ", key );
        m_rasters[key] = std::make_shared<Data::Raster>();
    }

    //--------------------------------------------------------------------------
    void DataServerLocal::createRasterProxy( const string & key, int w, int h,
                                              double x0, double x1, double y0, double y1 ){
        assert( false && "DataServerLocal::createRasterProxy can't be called" );
    }

}//namespace Engine

//------------------------------------------------------------------------------

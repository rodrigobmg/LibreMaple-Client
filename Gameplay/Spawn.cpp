//////////////////////////////////////////////////////////////////////////////
// This file is part of the LibreMaple MMORPG client                        //
// Copyright © 2015-2016 Daniel Allendorf, 2018-2019 LibreMaple Team        //
//                                                                          //
// This program is free software: you can redistribute it and/or modify     //
// it under the terms of the GNU Affero General Public License as           //
// published by the Free Software Foundation, either version 3 of the       //
// License, or (at your option) any later version.                          //
//                                                                          //
// This program is distributed in the hope that it will be useful,          //
// but WITHOUT ANY WARRANTY; without even the implied warranty of           //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            //
// GNU Affero General Public License for more details.                      //
//                                                                          //
// You should have received a copy of the GNU Affero General Public License //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.    //
//////////////////////////////////////////////////////////////////////////////
#include "Spawn.h"

#include "../Character/OtherChar.h"
#include "MapleMap/ItemDrop.h"
#include "MapleMap/MesoDrop.h"
#include "MapleMap/Mob.h"
#include "MapleMap/Npc.h"
#include "MapleMap/Reactor.h"

namespace jrc
{
NpcSpawn::NpcSpawn(std::int32_t o,
                   std::int32_t i,
                   Point<std::int16_t> p,
                   bool fl,
                   std::uint16_t f)
    : oid(o), id(i), position(p), flip(fl), fh(f)
{
}

std::int32_t NpcSpawn::get_oid() const
{
    return oid;
}

std::unique_ptr<MapObject> NpcSpawn::instantiate(const Physics& physics) const
{
    auto spawnposition = physics.get_y_below(position);
    return std::make_unique<Npc>(id, oid, flip, fh, false, spawnposition);
}

MobSpawn::MobSpawn(std::int32_t o,
                   std::int32_t i,
                   std::int8_t m,
                   std::int8_t st,
                   std::uint16_t f,
                   bool ns,
                   std::int8_t t,
                   Point<std::int16_t> p)
    : oid(o),
      id(i),
      mode(m),
      stance(st),
      fh(f),
      newspawn(ns),
      team(t),
      position(p)
{
}

std::int8_t MobSpawn::get_mode() const
{
    return mode;
}

std::int32_t MobSpawn::get_oid() const
{
    return oid;
}

std::unique_ptr<MapObject> MobSpawn::instantiate() const
{
    return std::make_unique<Mob>(
        oid, id, mode, stance, fh, newspawn, team, position);
}

ReactorSpawn::ReactorSpawn(std::int32_t o,
                           std::int32_t r,
                           std::int8_t s,
                           Point<std::int16_t> p)
    : oid(o), rid(r), state(s), position(p)
{
}

std::int32_t ReactorSpawn::get_oid() const
{
    return oid;
}

std::unique_ptr<MapObject>
ReactorSpawn::instantiate(const Physics& physics) const
{
    auto spawnposition = physics.get_y_below(position);
    return std::make_unique<Reactor>(oid, rid, state, spawnposition);
}

DropSpawn::DropSpawn(std::int32_t o,
                     std::int32_t i,
                     bool ms,
                     std::int32_t ow,
                     Point<std::int16_t> p,
                     Point<std::int16_t> d,
                     std::int8_t t,
                     std::int8_t m,
                     bool pd)
    : oid(o),
      id(i),
      meso(ms),
      owner(ow),
      start(p),
      dest(d),
      droptype(t),
      mode(m),
      playerdrop(pd)
{
}

bool DropSpawn::is_meso() const
{
    return meso;
}

std::int32_t DropSpawn::get_itemid() const
{
    return id;
}

std::int32_t DropSpawn::get_oid() const
{
    return oid;
}

std::unique_ptr<MapObject> DropSpawn::instantiate(const Animation& icon) const
{
    return std::make_unique<MesoDrop>(
        oid, owner, start, dest, droptype, mode, playerdrop, icon);
}

std::unique_ptr<MapObject> DropSpawn::instantiate(const Texture& icon) const
{
    return std::make_unique<ItemDrop>(
        oid, owner, start, dest, droptype, mode, id, playerdrop, icon);
}

CharSpawn::CharSpawn(std::int32_t c,
                     const LookEntry& lk,
                     std::uint8_t l,
                     std::int16_t j,
                     const std::string& nm,
                     std::int8_t st,
                     Point<std::int16_t> p)
    : cid(c), level(l), job(j), name(nm), stance(st), position(p), look(lk)
{
}

std::int32_t CharSpawn::get_cid() const
{
    return cid;
}

std::unique_ptr<MapObject> CharSpawn::instantiate() const
{
    return std::make_unique<OtherChar>(
        cid, look, level, job, std::string{name}, stance, position);
}
} // namespace jrc

#pragma once

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

namespace godot {

class PlayerDatabase : public RefCounted {
    GDCLASS(PlayerDatabase, RefCounted)

public:
    PlayerDatabase();
    ~PlayerDatabase();

    bool load_from_csv(const String& p_filepath);
    Dictionary get_player(const String& p_name) const;
    Array get_all_players() const;

protected:
    static void _bind_methods();

private:
    Dictionary player_map;
    Array player_list;
};

} // namespace godot
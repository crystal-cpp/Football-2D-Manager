#include "player_database.h"

using namespace godot;

void PlayerDatabase::_bind_methods() {
    ClassDB::bind_method(D_METHOD("load_from_csv", "filepath"), &PlayerDatabase::load_from_csv);
    ClassDB::bind_method(D_METHOD("get_player", "name"), &PlayerDatabase::get_player);
    ClassDB::bind_method(D_METHOD("get_all_players"), &PlayerDatabase::get_all_players);
}

PlayerDatabase::PlayerDatabase() {}
PlayerDatabase::~PlayerDatabase() {}

bool PlayerDatabase::load_from_csv(const String& p_filepath) {
    Ref<FileAccess> file = FileAccess::open(p_filepath, FileAccess::READ);
    if (file.is_null()) {
        UtilityFunctions::printerr("Failed to open player database CSV: ", p_filepath);
        return false;
    }

    bool is_header = true;
    while (!file->eof_reached()) {
        PackedStringArray row = file->get_csv_line();
        if (row.size() < 8) continue;

        if (is_header) {
            is_header = false;
            continue; // Skip header row
        }

        Dictionary player;
        player["name"] = row[0];
        player["position"] = row[1];
        player["pace"] = row[2].to_int();
        player["shooting"] = row[3].to_int();
        player["passing"] = row[4].to_int();
        player["dribbling"] = row[5].to_int();
        player["defending"] = row[6].to_int();
        player["physical"] = row[7].to_int();

        player_map[row[0]] = player;
        player_list.append(player);
    }

    UtilityFunctions::print("Loaded ", player_list.size(), " players into Godot DB.");
    return true;
}

Dictionary PlayerDatabase::get_player(const String& p_name) const {
    if (player_map.has(p_name)) {
        return player_map[p_name];
    }
    return Dictionary();
}

Array PlayerDatabase::get_all_players() const {
    return player_list;
}
#pragma once

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/dictionary.hpp>

namespace godot {

class MatchEngine : public Node2D {
    GDCLASS(MatchEngine, Node2D)

public:
    MatchEngine();
    ~MatchEngine();

    void _ready() override;
    void _physics_process(double delta) override;

    void start_match();
    void resolve_manual_scenario(bool p_success);

    Array get_player_positions() const;
    Vector2 get_ball_position() const;

protected:
    static void _bind_methods();

private:
    float match_timer = 0.0f;
    int current_minute = 0;
    int home_score = 0;
    int away_score = 0;
    bool is_paused_for_manual = false;

    Vector2 ball_position = Vector2(525.0f, 340.0f);
    Array player_positions;
};

} // namespace godot

-- inject database from pw --

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";

CREATE TABLE `arena_settings` (
  `week_time` int(11) NOT NULL DEFAULT 0,
  `max_bonus` int(11) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
COMMIT;

CREATE TABLE `arena_players` (
  `player_id` int(11) NOT NULL DEFAULT 0,
  `team_id` int(11) NOT NULL DEFAULT 0,
  `cls` int(11) NOT NULL DEFAULT 0,
  `score` int(11) NOT NULL DEFAULT 0,
  `win_count` int(11) NOT NULL DEFAULT 0,
  `team_score` int(11) NOT NULL DEFAULT 0,
  `week_battle_count` int(11) NOT NULL DEFAULT 0,
  `invite_time` int(11) NOT NULL DEFAULT 0,
  `last_visite` int(11) NOT NULL DEFAULT 0,
  `battle_count` int(11) NOT NULL DEFAULT 0,
  `name` varchar(64) NOT NULL DEFAULT ''
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

CREATE TABLE `arena_teams` (
  `team_id` int(11) NOT NULL,
  `captain_id` int(11) NOT NULL DEFAULT 0,
  `team_type` int(11) NOT NULL DEFAULT 0,
  `score` int(11) NOT NULL DEFAULT 0,
  `last_visite` int(11) NOT NULL DEFAULT 0,
  `win_count` int(11) NOT NULL DEFAULT 0,
  `team_score` int(11) NOT NULL DEFAULT 0,
  `week_battle_count` int(11) NOT NULL DEFAULT 0,
  `create_time` int(11) NOT NULL DEFAULT 0,
  `battle_count` int(11) NOT NULL DEFAULT 0,
  `name` varchar(64) NOT NULL DEFAULT '''''',
  `members` text NOT NULL DEFAULT '',
  `teams` text NOT NULL DEFAULT ''
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

ALTER TABLE `arena_teams`
  ADD PRIMARY KEY (`team_id`);

ALTER TABLE `arena_players`
  ADD PRIMARY KEY (`player_id`);
  
ALTER TABLE `arena_teams`
  MODIFY `team_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1;
  

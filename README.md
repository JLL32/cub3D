# cub3D



game {
	mlx
	win
	win_buffer
	player {}
}

env {
	resolution {}
	textures [4]
	colors {}
	world_map
	sprites
}

cg {
	mlx
	win
	win_buffer
}

# Engine
camera_x

ray_dir {
	x = player.dir_x + player.plane_x * camera_x
	y = player.dir_y + player.plane_y * camera_x
}

map {
	x = player.pos_x
	y = player.pos_y
}

side_dist {
	x =
	y =
}

delta_dist {
	x = fabs(1.0 / ray_dir_x)
	y = fabs(1.0 / ray_dir_y)
}

wall {
	dist
	side
	wall_x
	start
	end
}

detect_wall(player, screen, world_map) -> wall
draw_wall() -> void


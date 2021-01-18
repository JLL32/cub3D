# cub3D



game {
	mlx
	win
	win_buffer
	screen
	world_map
	player {}
	textures [4]
	colors {}
}

env {
	resolution {}
	textures [4]
	player {}
	colors {}
	world_map
}

cg {
	mlx
	win
	win_buffer
}

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

wall_collision {
	dist
	side
}

perp_wall_dist(player, screen, world_map) -> wall_collision

wall_x(perp_wall_dist, ray) -> int

tex_x(wall_x, perp_wall_dist, side) -> int



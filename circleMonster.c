#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "coords.h"
#include "ucircle.h"

void apply_behavior_monster(struct coords_t *monster, struct coords_t swimmer, double step, double monster_speed);
void apply_behavior_swimmer(struct coords_t *swimmer, struct coords_t monster, double step);
void print_locations(struct coords_t swimmer, struct coords_t monster);

// Just move to the closest point to the swimmer
void apply_behavior_monster(struct coords_t *monster, struct coords_t swimmer, double step, double monster_speed)
{
	double start = ucircle_coords_to_radians(coords_normalize(*monster));
	double goal = ucircle_coords_to_radians(coords_normalize(coords_copy(swimmer)));
	double path = goal - start;
	double speed = monster_speed / step;

	if (fabs(path) > speed)
		path = speed;

	*monster = ucircle_radians_to_coords(start + path);
}

// Go in the opposite direction from the monster (not optimal)
void apply_behavior_swimmer(struct coords_t *swimmer, struct coords_t monster, double step)
{
	struct coords_t direction = coords_normalize(coords_sum(*swimmer, coords_scale(-1, monster)));
	struct coords_t new_coords = coords_sum(*swimmer, coords_scale(1.0 / step, direction));
	if (coords_dot_product(new_coords, new_coords) > 1)
		*swimmer = coords_normalize(new_coords);
	else
		*swimmer = new_coords;
}

void print_locations(struct coords_t swimmer, struct coords_t monster)
{
	int scale = 10;
	for (int x = -scale; x <= scale; x++)
	{
		for (int y = -scale; y <= scale; y++)
		{
			if ((int)(swimmer.x * scale) == x && (int)(swimmer.y * scale) == y)
				printf("X ");
			else if ((int)(monster.x * scale) == x && (int)(monster.y * scale) == y)
				printf("V ");
			else if (sqrt(x * x + y * y) < scale)
				printf(". ");
			else
				printf("| ");
		}
		printf("\n");
	}
}

int main(int argc, char **argv)
{
	if (argc != 3)
		return -1;

	double step, monster_speed;
	sscanf(argv[1], "%lf", &step);
	sscanf(argv[2], "%lf", &monster_speed);

	struct coords_t swimmer = coords_init(0, 0);
	struct coords_t monster = coords_init(0, -1);

	int steps = 1;
	while (1)
	{
		apply_behavior_swimmer(&swimmer, monster, step);
		apply_behavior_monster(&monster, swimmer, step, monster_speed);

		printf("\nStep %d", steps++);
		printf("\nSwimmer: ");
		coords_print(swimmer);
		printf("\nMonster: ");
		coords_print(monster);
		printf("\n");

		print_locations(swimmer, monster);

		if (fabs(swimmer.x - monster.x) < 0.00001 && fabs(swimmer.y - monster.y) < 0.00001)
		{
			printf("Capture!\n");
			break;
		}

		if (coords_dot_product(swimmer, swimmer) == 1)
		{
			printf("Escape!\n");
			break;
		}
		sleep(1);
	}
	return 0;
}

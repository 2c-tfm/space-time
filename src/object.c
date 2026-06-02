#include <space_time.h>


object *objs;

static Color color_from_name(char *name) {
	uint8_t i = 0;
	char *names[] = {"LIGHTGRAY", "GRAY", "DARKGRAY", "YELLOW", "GOLD", "ORANGE", "PINK", "RED", "MAROON", "GREEN", "LIME", "DARKGREEN", "SKYBLUE", "BLUE", "DARKBLUE", "PURPLE", "VIOLET", "DARKPURPLE", "BEIGE", "BROWN", "DARKBROWN", "WHITE", "BLACK", "BLANK", "MAGENTA"};
	struct Color colors[] = {LIGHTGRAY, GRAY, DARKGRAY, YELLOW, GOLD, ORANGE, PINK, RED, MAROON, GREEN, LIME, DARKGREEN, SKYBLUE, BLUE, DARKBLUE, PURPLE, VIOLET, DARKPURPLE, BEIGE, BROWN, DARKBROWN, WHITE, BLACK, BLANK, MAGENTA};
	while (i < sizeof(colors) / sizeof(colors[0])) {
		if (strcmp(name, names[i]) == 0){
			return (colors[i]);
		}
		i++;
	}
	return (WHITE);
}

object *search_space_elem(char *name){
	object *obj_it = objs;

	while (obj_it != NULL){
		if (strcmp(name, obj_it->name) == 0)
			return (obj_it);
		obj_it = obj_it->next;
	}
	return (NULL);
}

object *init_space_elem(cJSON *elem){
	object *obj = MemAlloc(sizeof(object));
	cJSON	*entry;

	memset(obj, 0, sizeof(object));
	
	entry = cJSON_GetObjectItem(elem, "name");
	if (cJSON_IsString(entry))
		obj->name = strdup(entry->valuestring);

	entry = cJSON_GetObjectItem(elem, "mass");
	if (cJSON_IsNumber(entry))
		obj->mass = entry->valuedouble;

	entry = cJSON_GetObjectItem(elem, "radius");
	if (cJSON_IsNumber(entry))
		obj->radius = entry->valuedouble;

	entry = cJSON_GetObjectItem(elem, "coords");
	if (cJSON_IsObject(entry)) {
		obj->coords.x = cJSON_GetObjectItem(entry, "x")->valuedouble;
		obj->coords.y = cJSON_GetObjectItem(entry, "y")->valuedouble;
		obj->coords.z = cJSON_GetObjectItem(entry, "z")->valuedouble;
	}

	entry = cJSON_GetObjectItem(elem, "colors");

	if (cJSON_IsArray(entry)) {
		cJSON *c0 = cJSON_GetArrayItem(entry, 0);
		cJSON *c1 = cJSON_GetArrayItem(entry, 1);
		if (cJSON_IsString(c0))
			obj->colors[0] = color_from_name(c0->valuestring);
		if (cJSON_IsString(c1))
			obj->colors[1] = color_from_name(c1->valuestring);
	}

	entry = cJSON_GetObjectItem(elem, "secondaries");
	if (cJSON_IsArray(entry)) {
		uint32_t scount = cJSON_GetArraySize(entry);
		uint32_t i = 0;
		while (i < scount) {
			char * secondary_name = cJSON_GetArrayItem(entry, i)->valuestring;
			object *secondary = search_space_elem(secondary_name);
			if (secondary == NULL) {
				printf("%s will not orbit %s, please define it before.\n", secondary_name, obj->name);
				i++;
				continue;
			}
			calc_orbiter_velocity(secondary, obj);
			i++;
		}
	} else {
		puts("secondary objects must be in an array containing the name of orbiting objects");
	}
	return (obj);
}

static void print_space_object(object *obj){
	printf(
			"Space object [%s]\n"
			"\t\tMass [%lf]\n"
			"\t\tradius [%ld]\n"
			"\t\tacceleration x:[%lf] y:[%lf] z:[%lf]\n"
			"\t\tvelocity x:[%lf] y:[%lf] z:[%lf]\n",
			obj->name, obj->mass, obj->radius,
			obj->acceleration.x, obj->acceleration.y,
			obj->acceleration.z, 
			obj->velocity.x, obj->velocity.y, obj->velocity.z
		);
}


void print_all_space_object(){
	object *obj_it = objs;

	while (obj_it != NULL){
		print_space_object(obj_it);
		obj_it = obj_it->next;
	}
}

void init_space_objects(char *cfg){
	cJSON *root = cJSON_Parse(cfg);
	cJSON *objects_json = NULL;
	object *curr = NULL;
	uint32_t i = 0;
	uint32_t count = 0;

	if (root == NULL)
		return;
	
	objects_json = cJSON_GetObjectItem(root, "objects");
	if (!cJSON_IsArray(objects_json)) {
		cJSON_Delete(root);
		return;
	}

	count = cJSON_GetArraySize(objects_json);

	while (i < count){
		cJSON *currjson = cJSON_GetArrayItem(objects_json, i);
		if (curr != NULL){
			curr->next = init_space_elem(currjson);
			curr = curr->next;
		}
		else {
			curr = init_space_elem(currjson);
			objs = curr;
		}
		i++;
	}
}

// Standard Library
#include <iostream>
#include <vector>
#include <tuple>
#include <random>
#include <cmath>
#include <math.h>
#include <variant>
#include <numbers>
#include <direct.h>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <chrono>
#include <format>
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <commdlg.h>


#include <json.hpp>
using json = nlohmann::json;
// SFML Library

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
// Local Library






////////////////// Initialize Game Classes and Functions ///////////////////////////////////////////////////

class Entity;
class Laser;
class Missle;
class Particle;
class Tile;
class GameDisplayText;
class DeadTank;
class Button;




sf::Image transformImgCol(sf::Image img, sf::Color tcol);
bool compareTeam(const std::vector <int>& team1, const std::vector <int> team2);
void renderText(sf::RenderWindow& surface, const sf::Vector2f& pos, const std::string& Text, const sf::Font& font, int size, const sf::Color& fill_col, int outline_thickness = 0, const sf::Color& outline_col = { 0,0,0,255 }, bool centered = true);
void handleEvents(sf::RenderWindow& myWindow);
void keyboardInputs();
void drawBorders();
void ScreenShot(sf::RenderWindow& surface);

void DrawTiles();
void RenderEntities();
void RenderLasers();
void RenderParticles();
void RenderMissles();
void RenderMinimap();
void DrawUI(sf::RenderWindow& surface);
void RenderGameTexts(sf::RenderWindow& surface);
void RenderDeadTanks();
void RenderButtons();


void SpawnTank(sf::Vector2f pos, int team, int level = 0, bool no_ammo = false);
void SpawnFort(sf::Vector2f pos, int team, bool captured = false, bool special = false);
void SpawnLaser(float posx, float posy, float vel, float ang, float dam, float team, Entity* sender, std::vector <float> size = { 2, 1 });
void SpawnMissle(sf::Vector2f pos, float vel, float ang, float dam, int no_of_proj, int team, Entity* sender, Entity* target, float size, int trail_length, float splash_radius, float terminal_vel = 7.5, float power = 1);
void SpawnParticle(sf::Vector2f pos, float size, float range, int type, float durRate, sf::Color col);
void SpawnGameText(std::string Text, sf::Vector2f pos, sf::Color col, int size, float dur, float thickness, bool shadow = false);
void SpawnDeadTank(sf::Vector2f pos, float ang, int team);
void SpawnButton(sf::Vector2f pos, sf::Vector2f size, std::string text, sf::Color colour, int action, int text_size = 12);

bool checkLineCollision(sf::FloatRect rect, sf::Vector2f pos1, sf::Vector2f pos2);
bool lineSegmentIntersection(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f q1, sf::Vector2f q2);

void drawFilledRect(sf::RenderWindow& myWindow, const sf::FloatRect& rect, sf::Color col);
void drawLine(sf::RenderWindow& wind, sf::Vector2f pos1, sf::Vector2f pos2, sf::Color col);
void drawRect(sf::RenderWindow& myWindow, sf::FloatRect rect, sf::Color col, int thickness);
void drawFilledCircle(sf::RenderWindow& myWindow, sf::Vector2f center, float radius, sf::Color col);
void drawCircle(sf::RenderWindow& myWindow, sf::Vector2f center, float radius, sf::Color col, int thickness);
void drawArc(sf::RenderWindow& myWindow, sf::Vector2f center, float radius, sf::Color col, int thickness, float startAngle, float endAngle, int pointCount = 16);
void drawRegPolygon(sf::RenderWindow& myWindow, sf::Vector2f center, float radius, sf::Color col, int thickness, int sides, float rotation, bool fill);
void drawThickLine(sf::RenderWindow& wind, sf::Vector2f pos1, sf::Vector2f pos2, float thickness, sf::Color color);


sf::Color dimCol(sf::Color col, float perc);
sf::Color oppCol(const sf::Color& col);
sf::Color stage_Colour();

int getTankPop(int team);
int getFortPop(int team, bool captured = false);
int getSpecialTankPop(int team);
int getSpecialFortPop(int team);
int getAverageTankAge(int team);
int getTerritory(int team);
void updateStageColour();
void UpdateTiles();
void InitTiles();
void DemoGame(int type = 0);

void updateWind();
void loadGameButtons();
void updateStats();
void saveJSONData();


sf::Vector2f scaleVector (sf::Vector2f &vector, float magnitude);
float displacement(sf::Vector2f& vec_1, sf::Vector2f& vec_2);

void saveGameState(const std::string& filename);


std::string getDateString();
std::string getTimeString();


std::string OpenFileDialog(const char* filter = "All Files\0*.*\0", HWND owner = NULL);

Entity* checkEntity(Entity* entity);

std::vector<Tile*> getTileNeighbors(Tile& tile);




bool eventLogging = false;
bool devWindow = false;
sf::Image  TankImg; sf::Image FortImg; sf::Image DeadTankImg[2];
sf::RenderWindow  window;
bool quitGame = false;


float GameFPSRatio;
int summonTeam = 0;


// SFX and Music
sf::Music background_Music;

sf::SoundBuffer b_tankshoot01;
sf::Sound tankshoot01(b_tankshoot01);
sf::SoundBuffer b_tankshoot02;
sf::Sound tankshoot02(b_tankshoot02);

sf::SoundBuffer b_fortshoot01;
sf::Sound fortshoot01(b_fortshoot01);

sf::SoundBuffer b_tankdies01;
sf::Sound tankdies01(b_tankdies01);
sf::SoundBuffer b_tankdies02;
sf::Sound tankdies02(b_tankdies02);

sf::SoundBuffer b_fortcaptured01;
sf::Sound fortcaptured01(b_fortcaptured01);

sf::SoundBuffer b_laserhit01;
sf::Sound laserhit01(b_laserhit01);

sf::SoundBuffer b_tankreload01;
sf::Sound tankreload01(b_tankreload01);

sf::SoundBuffer b_tankcreated01;
sf::Sound tankcreated01(b_tankcreated01);


// Game Fonts
sf::Font GameFont;
sf::Font SecondaryFont;


// float SCREEN_WIDTH = 1366; float SCREEN_HEIGHT = 768;
float GAME_MAP_WIDTH = 2500; float GAME_MAP_HEIGHT = 2500;
float MINIMAP_WIDTH = 250; float MINIMAP_HEIGHT = 250;


const int numberOfTeams = 16;
sf::Color colorArr[numberOfTeams] = {
	{0, 0, 255},
	{255, 0, 0},
	{0, 255, 0},
	{255, 255, 0},
	{255, 32, 128},
	{128, 0, 255},
	{0, 32, 128},
	{128, 48, 0},
	{32, 85, 0},
	{255, 128, 0},
	{0, 255, 128},
	{150, 119, 75},
	{170, 0, 85},
	{0, 128, 255},
	{254, 254, 254},
	{85, 85, 85}
};

int TeamTileNo[numberOfTeams] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
float TeamTilePerc[numberOfTeams] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

bool recording = false;
std::vector <std::array <int, numberOfTeams>> TankPopArr;
std::vector <std::array <int, numberOfTeams>> FortPopArr;
std::vector <std::array <int, numberOfTeams>> SpecialTankPopArr;
std::vector <std::array <int, numberOfTeams>> SpecialFortPopArr;
std::vector <std::array <int, numberOfTeams>> TanksKilledArr;
std::vector <std::array <int, numberOfTeams>> TanksLostArr;
std::vector <std::array <int, numberOfTeams>> AverageTankAgeArr;
std::vector <std::array <int, numberOfTeams>> TeamTerritoryArr;
std::vector <std::array <int, numberOfTeams>> CapturedFortPopArr;

std::vector <std::array <float, numberOfTeams>> SpecialTankRatioArr;
std::vector <std::array <float, numberOfTeams>> SpecialFortRatioArr;
std::vector <std::array <float, numberOfTeams>> CapturedFortRatioArr;


int temp_Tank_Pop[numberOfTeams];
int temp_Fort_Pop[numberOfTeams];
int temp_Captured_Fort_Pop[numberOfTeams];
int temp_Special_Tank_Pop[numberOfTeams];
int temp_Special_Fort_Pop[numberOfTeams];


std::string TeamNameArr[numberOfTeams] = {
	"Blue", "Red",    "Green",   "Yellow",
	"Pink", "Purple", "Cyan",    "Brown",
	"Grey", "Orange", "CyGreen", "Khaki",
	"Wine", "Turquoise"
};
int FPS = 60;

sf::Image CompTankImgArr[numberOfTeams]; sf::Texture CompTankTextArr[numberOfTeams];
sf::Image FortImgArr[numberOfTeams]; sf::Texture FortTextArr[numberOfTeams];
sf::Image DeadTankImgArr[numberOfTeams][2]; sf::Texture DeadTankTextArr[numberOfTeams][2];
sf::Vector2f Mouse_Pos;


std::vector <Entity> EntityArr;
std::vector <Laser> LaserArr;
std::vector <Missle> MissleArr;
std::vector <Particle> ParticleArr;
std::vector <Tile> TileArr;
std::vector <GameDisplayText> GameTextArr;
std::vector <DeadTank> DeadTankArr;
std::vector <Button> ButtonArr;



int Tanks_Killed[numberOfTeams];
int Forts_Destroyed[numberOfTeams];
int Tanks_Lost[numberOfTeams];
int Forts_Lost[numberOfTeams];

int PvP_Tanks_Killed[numberOfTeams];
int PvP_Tanks_Lost[numberOfTeams];



int tankFollowed;
sf::FloatRect GameScreenRect;
sf::Color StageColour;



////////////////////// GAME VARIABLES /////////////////////////////////
int game_ticks = 0;

// Game Rules

std::ifstream GameRuleFile("GameRules.json");
json _jData_GameRules = json::parse(GameRuleFile);

bool NEED_SUPPLIES =				_jData_GameRules["NEED_SUPPLIES"];
bool CONVERT_FORTS =				_jData_GameRules["CONVERT_FORTS"];
bool CONVERT_TANKS =				_jData_GameRules["CONVERT_TANKS"];
bool GIFT_TANKS =					_jData_GameRules["GIFT_TANKS"];
bool FORTS_SPAWN_TANKS =			_jData_GameRules["FORTS_SPAWN_TANKS"];
bool FORTS_ATTACK_FORTS =			_jData_GameRules["FORTS_ATTACK_FORTS"];
bool FORTS_NEUTERED =				_jData_GameRules["FORTS_NEUTERED"];
bool FORT_MISSLES =					_jData_GameRules["FORT_MISSLES"];
bool FORT_HEALING =					_jData_GameRules["FORT_HEALING"];
bool SPECIAL_TANKS =				_jData_GameRules["SPECIAL_TANKS"];
bool SPECIAL_FORTS =				_jData_GameRules["SPECIAL_FORTS"];









// Class Unit Values
std::ifstream EntityValueFile("EntityValues.json");
json _jsonData01 = json::parse(EntityValueFile);

const int extra_population_interval	=	_jsonData01["extra_population_interval"];
const int extra_population_quanta =		_jsonData01["extra_population_quanta"];

const int Tank_MAX_AMMO =			_jsonData01["Tank_MAX_AMMO"];
const int Tank_MISSLE_NO =			_jsonData01["Tank_MISSLE_NO"];
const int Tank_MAX_POP =			_jsonData01["Tank_MAX_POP"];
const float Tank_SPEED_FACTOR =		_jsonData01["Tank_SPEED_FACTOR"];
const int Tank_LASER_COOLDOWN =		_jsonData01["Tank_LASER_COOLDOWN"];

const int Fort_SPAWNTANK_TIME =		_jsonData01["Fort_SPAWNTANK_TIME"];
const int Fort_LASER_COOLDOWN =		_jsonData01["Fort_LASER_COOLDOWN"];
const int Fort_SIZE =				_jsonData01["Fort_SIZE"];

// Standard Unit Values
const float Tank_HP =				_jsonData01["Tank_HP"];
const int Tank_RANGE =				_jsonData01["Tank_RANGE"];
const float Tank_DAMAGE =			_jsonData01["Tank_DAMAGE"];

const float Fort_HP =				_jsonData01["Fort_HP"];
const int Fort_RANGE =				_jsonData01["Fort_RANGE"];
float Fort_DAMAGE =			_jsonData01["Fort_DAMAGE"];

float PanicHealthPerc =				_jsonData01["PanicHealthPerc"];


// Special Unit Values

int special_tank_age =						_jsonData01["special_tank_age"];
int special_tank_killcount =				_jsonData01["special_tank_killcount"];

float special_tank_damage_factor =			_jsonData01["special_tank_damage_factor"];
float special_tank_ammo_factor =			_jsonData01["special_tank_ammo_factor"];
float special_tank_hitpoints_factor =		_jsonData01["special_tank_hitpoints_factor"];
float special_tank_healing_factor =			_jsonData01["special_tank_healing_factor"];
float special_tank_speed_factor =			_jsonData01["special_tank_speed_factor"];
float special_tank_range_factor =			_jsonData01["special_tank_range_factor"];

int special_fort_tanks_healed =				_jsonData01["special_fort_tanks_healed"];
int special_fort_tanks_spawned =			_jsonData01["special_fort_tanks_spawned"];

float special_fort_hitpoints_factor =		_jsonData01["special_fort_hitpoints_factor"];
float special_fort_healing_factor =			_jsonData01["special_fort_healing_factor"];
float special_fort_tankspawn_factor =		_jsonData01["special_fort_tankspawn_factor"];
float special_fort_misslecooldown_factor =	_jsonData01["special_fort_misslecooldown_factor"];
float special_fort_damage_factor =			_jsonData01["special_fort_damage_factor"];
float special_fort_range_factor =			_jsonData01["special_fort_range_factor"];
float special_fort_territory_power =		_jsonData01["special_fort_territory_power"];

float assimilating_fort_territory_power =	_jsonData01["assimilating_fort_territory_power"];

// Entity Constant Values

float fort_missle_cooldown_factor =		_jsonData01["fort_missle_cooldown_factor"];
int fort_target_time =					_jsonData01["fort_target_time"];
int fort_wander_time =					_jsonData01["fort_wander_time"];
int fort_gun_length =					_jsonData01["fort_gun_length"];
int fort_gun_width =					_jsonData01["fort_gun_width"];
int tank_supplyammo_ticks =				_jsonData01["tank_supplyammo_ticks"];
int tank_target_ticks =					_jsonData01["tank_target_ticks"];
float tank_LOSrange_factor =			_jsonData01["tank_LOSrange_factor"];

float tank_fort_heal_percent =			_jsonData01["tank_fort_heal_percent"];
float tanks_per_fort =					_jsonData01["tanks_per_fort"];

int fort_assimilation_ticks =			_jsonData01["fort_assimilation_ticks"];
int fort_validhealer_ticks =			_jsonData01["fort_validhealer_ticks"];


int maxTankHealArray =					_jsonData01["fort_healing_lobby_size"];


// Missle Constant Values
float tank_missle_velocity =			_jsonData01["tank_missle_velocity"];
float tank_missle_damagefactor =		_jsonData01["tank_missle_damagefactor"];
int tank_missle_projectile_no  =		_jsonData01["tank_missle_projectile_no"];
float tank_missle_splash_radius  =		_jsonData01["tank_missle_splash_radius"];
float tank_missle_terminal_velocity =	_jsonData01["tank_missle_terminal_velocity"];
float tank_missle_power  =				_jsonData01["tank_missle_power"];

float fort_missle_velocity =			_jsonData01["fort_missle_velocity"];
float fort_missle_damagefactor =		_jsonData01["fort_missle_damagefactor"];
int fort_missle_projectile_no =			_jsonData01["fort_missle_projectile_no"];
float fort_missle_splash_radius =		_jsonData01["fort_missle_splash_radius"];
float fort_missle_terminal_velocity =	_jsonData01["fort_missle_terminal_velocity"];
float fort_missle_power =				_jsonData01["fort_missle_power"];

bool SHINYS_MOVE_FAST =					_jsonData01["SHINYS_MOVE_FAST"];
bool DAMAGED_MOVE_FAST =				_jsonData01["DAMAGED_MOVE_FAST"];





// Graphics constants
std::ifstream GraphicsFile("Graphics.json");
json _jsonGraphicsData = json::parse(GraphicsFile);

float SCREEN_WIDTH = _jsonGraphicsData["SCREEN_WIDTH"];
float SCREEN_HEIGHT = _jsonGraphicsData["SCREEN_HEIGHT"];


float DefaultPartTimer =			_jsonGraphicsData["Default_Particle_Ticks"];
float TransRangeFort =				_jsonGraphicsData["Fort_BloomRangeFactor"];
float TransRangeTank =				_jsonGraphicsData["Tank_BloomRangeFactor"];
int dimColPerc = 75;
float Tiles_Size =					_jsonGraphicsData["Tiles_Size"];
int GameTextMaxTime =				_jsonGraphicsData["GameText_Ticks"];
int DeadTankLife =					_jsonGraphicsData["DeadTank_Ticks"];

// Missle graphics
float Tank_Missle_Size =			_jsonGraphicsData["Tank_Missle_Size"];
float Tank_Missle_TrailLength =		_jsonGraphicsData["Tank_Missle_TrailLength"];
float Fort_Missle_Size =			_jsonGraphicsData["Fort_Missle_Size"];
float Fort_Missle_TrailLength =		_jsonGraphicsData["Fort_Missle_TrailLength"];

// Wind
bool WIND_Physics =					_jsonGraphicsData["WIND"];
float WIND_max_speed_factor =		_jsonGraphicsData["max_wind_speed_factor"];
float WIND_strength_factor =		_jsonGraphicsData["wind_strength_factor"];

const int tankTrailLength =			_jsonGraphicsData["tank_trail_length"];
const float fortFlagNodeLength =		_jsonGraphicsData["flag_node_length"];
const int fortFlagNodeNumber =		_jsonGraphicsData["flag_node_number"];








// Graphics rules
bool interlocking_tiles = true;
bool draw_transp_fort = true;
bool draw_transp_tank = true;
bool draw_fort_stats = true;

bool fort_flicker = true;  // not active
bool cell_shading = false;  // not used
bool hexagon_tiles = false; // not used
bool colouredFPS = true;  // not used



// Toggle Values
bool DEBUG_FEATURES = false;
bool draw_particles = true;
bool draw_minimap = true;
bool draw_UI = true;
bool draw_Tiles = true;






// Graphical variables
float Camera_Pos[2] = { 0,0 };
bool Camera_Follow_Tank = false;
bool random_follow = false;
Entity* Tank_Followed;
int Tank_Followed_uniqueID;
std::string GameText;
int GameTextTime = 0;
int winner;
float LastFPS;
sf::Vector2f wind_vel;



sf::FloatRect MiniMapRect;


// Game Settings
float SCROLL_SENSITIVITY = 15;
bool paused = false;
float game_volume = 100;


int current_game_timer = 0;
int extra_population = 0;

std::vector <std::array <float, 2>> TankDeathPositions;

// GAME VARIABLES END //////////////////////////////////////









class Entity
{
public:
	std::string ID;								// Entty type {Tank or Fort}
	float pos[2], vel[2], acc[2];			// Position, Velocity, Acceleration  [Tank, Fort]
	sf::FloatRect rect;						// SFML rect object [Tank. Fort]
	float ang;								// Angle of entity [Tank, Fort]
	float v_ang, a_ang;						// Angular velocity and acceeration [Tank, Fort]
	int texWidth, texHeight;				// Dimensons of textures [Tank, Fort*]
	float wander_time, max_wander_time;		// Wander timing [Tank, Fort]
	float hp, max_hp;						// HitPoints [Tank, Fort]
	float dam;								// Damage points [Tank, Fort]
	float range;							// Range entity can attack [Tank, Fort]
	bool ia, idle;							// (i)n(a)cation and idle state [Tank, Fort]
	float targ_ang;							// target angle [Tank, Fort]
	int team;								// Entity team [Tank, Fort]
	sf::Color col, opp_col;							// Entity team colour [Fort]

	sf::Vector2f wander_pos;				// Wander target position [Tank]
	sf::Vector2f target_pos;				// Target position
	float max_laser_cooldown;
	float laser_cooldown;
	float max_ammo_supply;
	int ammo_supply;
	bool no_ammo;
	float max_ammo_supply_time;
	float ammo_supply_timer;

	Entity* ammo_Target; int ammo_Target_uID;
	Entity* enemy;
	Laser* last_bullet;
	int last_bullet_team; std::string last_bullet_ID; Entity* last_bullet_sender;
	int tilt_preference;
	float lock_target_timer;
	float max_lock_target_time;
	
	std::string enemyString;
	int kill_count, kill_count_threshold;
	int uniqueID;
	int enemy_uID;
	
	sf::Sprite entitySprite;
	int chunk[2];

	float age, old_age;

	// Fort Values
	int gun_barrel[2];
	float max_target_time, target_time;
	float max_flicker_time, flicker_vel, flicker_timer;
	float max_Tank_spawn_time, Tank_spawn_timer;
	float size;
	float max_missle_cooldown, missle_cooldown;

	int level;
	int fort_level, fort_tanks_healed, fort_tanks_spawned;
	int fort_tanks_spawned_threshold, fort_tanks_healed_threshold;

	std::vector <int> HealTankArray;

	bool special;


	// Arc angles
	float tank_health_arc_angle, fort_health_arc_angle, fort_assimilation_arc_angle;



	Entity(const std::string stringID) :
		ammo_Target(nullptr),
		enemy(nullptr),
		last_bullet(nullptr),
		last_bullet_sender(nullptr),
		ID(stringID),
		pos{ 0,0 }, vel{ 0,0 }, acc{ 0,0 },
		rect{},
		ang(0),
		v_ang(0), a_ang(0),
		texWidth(0), texHeight(0),
		max_wander_time(0),
		hp(0), max_hp(0),
		dam(0), range(0),
		ia(false), idle(false),
		targ_ang(0), team(-1), col{}, opp_col{},

		wander_pos{ 0,0 }, wander_time(0),
		target_pos{ 0,0 }, max_laser_cooldown(0),
		laser_cooldown(0), max_ammo_supply(0),
		ammo_supply(0), no_ammo(false),
		max_ammo_supply_time(0), ammo_supply_timer(0),

		ammo_Target_uID(-1),
		last_bullet_team(-1), last_bullet_ID(""),
		tilt_preference(0),
		lock_target_timer(0), max_lock_target_time(0),

		enemyString(""),
		kill_count(0), kill_count_threshold(0),
		uniqueID(-1), enemy_uID(-1),
		entitySprite{}, chunk{ 0,0 },
		age(0), old_age(0),

		gun_barrel{ 0,0 }, max_target_time(0), target_time(0),
		max_flicker_time(0), flicker_vel(0), flicker_timer(0),

		max_Tank_spawn_time(0), Tank_spawn_timer(0),
		size(0), max_missle_cooldown(0), missle_cooldown(0),

		level(0), fort_level(0), fort_tanks_healed(0), fort_tanks_spawned(0),
		fort_tanks_spawned_threshold(0), fort_tanks_healed_threshold(0),
		HealTankArray{}, special(false),
		tank_health_arc_angle(0), fort_health_arc_angle(0), fort_assimilation_arc_angle(0)
	{
		
		if (ID == "tank") {
			if (eventLogging) {
				std::cout << std::endl;
				std::cout << "Tank()" << std::endl;
				std::cout << std::endl;
			}

	
			enemyString = "tank";
			
			max_wander_time = 300;
			max_laser_cooldown = (float)Tank_LASER_COOLDOWN;
			max_ammo_supply = (float)Tank_MAX_AMMO;
			ammo_supply = (int)max_ammo_supply;
			max_ammo_supply_time = (float)tank_supplyammo_ticks;
			old_age = (float)special_tank_age;
			kill_count_threshold = special_tank_killcount;
		}

		if (ID == "fort") {
			if (eventLogging) {
				std::cout << std::endl;
				std::cout << "Fort()" << std::endl;
				std::cout << std::endl;
			}

			gun_barrel[0] = fort_gun_length; gun_barrel[1] = fort_gun_width;
		
			ang = rand() % 360;

			max_target_time = fort_target_time; target_time = max_target_time;
			idle = true;
			max_wander_time = fort_wander_time; wander_time = max_wander_time;
			max_laser_cooldown = Fort_LASER_COOLDOWN; 
			max_missle_cooldown = max_laser_cooldown * 33 * fort_missle_cooldown_factor;
			max_Tank_spawn_time = Fort_SPAWNTANK_TIME;
			max_flicker_time = 120; flicker_vel = 1;
			flicker_timer = rand() % (int)max_flicker_time;
			fort_tanks_healed_threshold = special_fort_tanks_healed; fort_tanks_spawned_threshold = special_fort_tanks_spawned;
		
		}
	}

	void spawn(sf::Vector2f spawn_pos, int spawn_team)
	{
		col = colorArr[team]; opp_col = oppCol(colorArr[team]);
		if (true) {
			bool uniqueIDfound = false;
			if (eventLogging) { std::cout << "  Finding Unique Id" << std::endl; }
			while (!uniqueIDfound) {
				uniqueID = rand();
				uniqueIDfound = true;
				for (int i = 0; i < EntityArr.size(); i++) {
					if ((EntityArr[i].uniqueID == uniqueID) or uniqueID == 0) {
						uniqueIDfound = false;
						if (eventLogging) { std::cout << "  Unique ID: " << uniqueID << " already in use; finding new id..." << std::endl; }
						break;
					}
				}
			}
			if (eventLogging) { std::cout << "  Entity spawned with Unique ID: " << uniqueID << std::endl; }
		}
		
		if (ID == "tank") {
			if (eventLogging) { 
				std::cout << "  Tank spawned; GameTick: " << game_ticks << std::endl;
			}

			team = spawn_team;
			col = colorArr[team]; opp_col = oppCol(col);
			ia = true;
			
			

			pos[0] = spawn_pos.x;
			pos[1] = spawn_pos.y;


			
			
			rect.width = CompTankImgArr[team].getSize().x;
			rect.height = CompTankImgArr[team].getSize().y;
			rect.left = spawn_pos.x + (rect.width / 2);
			rect.top = spawn_pos.y + (rect.height / 2);

			texWidth = CompTankTextArr[team].getSize().x; texHeight = CompTankTextArr[team].getSize().y;
			entitySprite.setTexture(CompTankTextArr[team]);

			

			if (eventLogging) {
				std::cout << "  Coordinates: " << pos[0] << ", " << pos[1] << std::endl;
			}

			hp = Tank_HP; max_hp = Tank_HP;
			dam = Tank_DAMAGE; range = Tank_RANGE;
			// LOS_range = range * tank_LOSrange_factor;
			ang = rand() % 360;
			lock_target_timer = 0; max_lock_target_time = tank_target_ticks;
			idle = false;
			enemy = nullptr; ammo_Target = nullptr;
			lockTarget();
			sf::Color col = colorArr[team];
			kill_count = 0;

		}

		if (ID == "fort")
		{
			if (eventLogging) {
				std::cout << "  Fort spawned; GameTick: " << game_ticks << std::endl;
			}



			ia = true;
			max_hp = Fort_HP; hp = max_hp;
			pos[0] = spawn_pos.x; pos[1] = spawn_pos.y;
			range = Fort_RANGE;
			dam = Fort_DAMAGE;
			team = spawn_team;
			col = colorArr[team]; opp_col = oppCol(col);
			size = Fort_SIZE;

			rect = {pos[0] - size/2, pos[1] - size/2, size, size};
			col = colorArr[team];
			ang = rand() % 360;

			
			texWidth = FortTextArr[team].getSize().x; texHeight = FortTextArr[team].getSize().y;
			entitySprite.setTexture(FortTextArr[team]);


		}

	}

	void AI();

	void move();

	void draw();

	void tilt(int dirc)
	{
		if (ID == "tank") {
			a_ang = .3 * dirc;
		}
		if (ID == "fort") {
			a_ang = .1 * dirc;
		}
	}

	void accel(float dirc)
	{
		if (ID == "tank") {
			acc[0] = cos(std::numbers::pi * ang / 180) * .075 * dirc * Tank_SPEED_FACTOR;
			acc[1] = sin(std::numbers::pi * ang / 180) * .075 * dirc * Tank_SPEED_FACTOR;
		}
	}

	void deccel()
	{
		if (ID == "tank") {
			for (int i = 0; i < 2; i++) {
				acc[i] = 0;

				// Don't forget GameFPSRatio
				vel[i] *= (float)pow(.1, GameFPSRatio);
				if (vel[i] <= .01) {
					vel[i] = 0;
				}
			}
		}
	}

	void deccelAng()
	{
		if (ID == "tank") {
			a_ang = 0;
			// Rememer GameFPSRatio
			v_ang *= (float)pow(.1, GameFPSRatio);
			if (v_ang <= 1) {
				v_ang = 0;
			}
		}
	}

	sf::FloatRect collisionRect() {
		if (ID == "tank") 
		{
			double radians = (ang - 90) * std::numbers::pi / 180.0;
			int width = abs(texWidth * cos(radians)) + abs(texHeight * sin(radians));
			int height = abs(texWidth * sin(radians)) + abs(texHeight * cos(radians));
			sf::FloatRect rotatedRect(pos[0] - width / 2, pos[1] - height / 2, width, height );
			return rotatedRect;
		}

		if (ID == "fort")
		{
			return rect;
		}
	}

	void lockTarget()
	{
		if (ID == "tank") {

			if (eventLogging) {
				std::cout << "Tank.lockTarget(); Gametick: " << game_ticks << std::endl;
			}

			int pass;
			

			// int small_dis = LOS_range * 100;
			int small_dis = -1;
			bool found = false;
			//Entity *entityID;
			enemy = nullptr;
			target_pos = { pos[0], pos[1] };
			for (Entity &entity : EntityArr) {
				if (entity.ia && entity.team != team) {
					int dx = pos[0] - entity.pos[0];
					int dy = pos[1] - entity.pos[1];

					double dis = std::sqrt(dx * dx + dy * dy);


					if (dis < small_dis || small_dis == -1) {
						small_dis = dis;
						found = true;
						this->enemy = &entity;
						enemy_uID = entity.uniqueID;

					}
					if (dis < range * 1.25 && entity.no_ammo && false) {
						// abandoned code
						pass = 1;
					}

				}
			}

			if (found) {
				//enemy = entityID;
				idle = false;
				wander_time = 0;
				if (eventLogging) {
					std::cout << "  Entity Found: " << enemy->ia << "; EnemyPos : " << enemy->pos[0] << "," << enemy->pos[1] << std::endl;
					std::cout << "  Enemy Team: " << enemy->team << std::endl;
				}

			}
			else {
				if (eventLogging) {
					std::cout << "  Enemy Not Found" << std::endl;
				}

				if (wander_time <= 0)
					wander();
				idle = true;
				enemy_uID = -1;
			}

			// Some more abandoned code

		}

		if (ID == "fort")
		{
			if (eventLogging) {
				std::cout << "Fort.lockTarget()" << std::endl;
			}

			if (!FORTS_NEUTERED) {
				float small_dis = range;
				bool found = false;

				// Find Target for Fort
				double dx, dy, dis;
				if (Tank_spawn_timer > 0) {
					for (int i = 0; i < EntityArr.size(); i++) {
						if (EntityArr[i].ia && EntityArr[i].team != team) {
							if (FORTS_ATTACK_FORTS || EntityArr[i].ID == "tank") {
								
								
								dx = pos[0] - EntityArr[i].pos[0];
								dy = pos[1] - EntityArr[i].pos[1];
								dis = std::sqrt(dx * dx + dy * dy);

								if (dis < small_dis) {
									small_dis = dis;
									found = true;
									enemy = &EntityArr[i];
									enemy_uID = EntityArr[i].uniqueID;
								}
							
							}
						}
					}
				}
			
				if (found) {
					idle = false; wander_time = 15;
					target_pos = { enemy->pos[0], enemy->pos[1]};
				}
				else {
					idle = true;
					enemy = nullptr;
					wander_time = max_wander_time;
					float dis = rand() % (int)(range + 1);
					float temp_ang = rand() % 360;

					float x = cos(temp_ang * std::numbers::pi / 180) * dis + pos[0];
					float y = sin(temp_ang * std::numbers::pi / 180) * dis + pos[1];
					target_pos = {x, y};
				}
			}
		}
	}

	void wander()
	{
		if (ID == "tank") {
			wander_time = max_wander_time;
			wander_pos = { pos[0] + (rand() % 300) - 150, pos[1] + (rand() % 300) - 150 };
		}

	}

	float getTerritoryPower() {
		if (ID == "fort") {
			if (eventLogging) { std::cout << "Fort.getTerritoryPower()" << std::endl; }
			if (Tank_spawn_timer < 0) { return assimilating_fort_territory_power; }
			if (special) {
				return special_fort_territory_power;
			}
			else {
				return 1.0f;
			}
		}
	}
	bool isAssimilating() {
		if (ID == "fort") {
			if (eventLogging) { std::cout << "Fort.isAssimilating()" << std::endl; }
			if (Tank_spawn_timer < 0) { return true; }
			else { return false; }
		}
		return false;
	}

	
	
};



class Laser
{
public:
	sf::Vector2f pos, last_pos, vel;
	int team;
	bool ia;
	sf::Color col, actual_col;
	int uniqueID;
	float dam, life, max_life;
	Entity* sender;
	int chunks[2];
	std::string sender_ID;
	int sender_uniqueID;
	std::vector <float> size;

	bool lost_sender;



	Laser() 
	{
		ia = false;
		max_life = 60;
	}

	bool spawn(sf::Vector2f spawn_pos, float spawn_vel, float ang, float spawn_dam, int spawn_team, Entity* spawn_sender, std::vector <float> sp_size)
	{
		if (eventLogging) { std::cout << "Laser.spawn()"; }

		if (spawn_sender == nullptr) {
			if (eventLogging) { std::cout << "  Laser.spawn() cancelled due to faulty sender..."; }; return false;
		}
		if (team >= numberOfTeams || team < 0) {
			if (eventLogging) { std::cout << "  Laser.spawn() cancelled due to memory leak..."; }; return false;
		}

		ia = true;
		dam = spawn_dam;
		pos = spawn_pos;
		last_pos = pos;
		team = spawn_team;
		vel = sf::Vector2f((cos(ang * std::numbers::pi / 180) * spawn_vel), (sin(ang * std::numbers::pi / 180) * spawn_vel) );
		life = max_life;
		size = sp_size;

		
		sender = spawn_sender;
		lost_sender = false;
		
		col = oppCol(colorArr[team]);
		actual_col = dimCol(col, dimColPerc);

		
		

		if (sender != nullptr && sender->ID.length() <= 4) { 
			if (eventLogging) { std::cout << "  accessing sender pointer..." << std::endl; }; 
			sender_ID = sender->ID;
			sender_uniqueID = sender->uniqueID;
		}
		else {ia = false; return false; }
		
		

		if (eventLogging) { std::cout << "  Laser.spawn() successful"; }
		return true;
	}

	void move() 
	{
		if (eventLogging) { std::cout << "Laser.move()" << std::endl; }
		if (sender != nullptr) {
			bool is_valid(false);
			for (auto& entity : EntityArr) {
				if (&entity == sender) {
					is_valid = true;
					break;
				}
			}
			if (!is_valid) {
				sender = nullptr;
				lost_sender = true;
			}
		}

		if ((sender == nullptr || sender->uniqueID != sender_uniqueID) && !lost_sender) {
			sender = nullptr;
			for (int i = 0; i < EntityArr.size(); i++) {
				if (EntityArr[i].uniqueID == sender_uniqueID && EntityArr[i].team == team && EntityArr[i].ID == sender_ID) {
					sender = &EntityArr[i];
					break;
				}
			}
			if (sender == nullptr) { lost_sender = true; } // Prevent performance lag
		}



		life -= GameFPSRatio;
		if (life <= 0) { ia = false; }

		last_pos = pos;
		pos.x += vel.x * GameFPSRatio; pos.y += vel.y * GameFPSRatio;


		sf::FloatRect laserBoundingBox(std::min(pos.x, last_pos.x), std::min(pos.y, last_pos.y), std::abs(pos.x - last_pos.x), std::abs(pos.y - last_pos.y));



		// Calculate Entity Collisions
		if (eventLogging) { std::cout << "  Laser Collision check" << std::endl; }
		for (Entity &entity : EntityArr) {
			if (entity.ia && entity.team != team) {
				if ((FORTS_ATTACK_FORTS || sender_ID != "fort" || entity.ID == "tank") && entity.hp >= 0) {
					if (laserBoundingBox.intersects(entity.collisionRect())) {
						if (checkLineCollision(entity.collisionRect(), pos, last_pos)) {
							ia = false;
							entity.hp -= dam;
							entity.last_bullet = this;
							entity.last_bullet_team = team;

							// Update Kill count of sender
							if (sender != nullptr && sender_uniqueID == sender->uniqueID && entity.hp <= 0 && entity.ID == "tank") {
								sender->kill_count += 1;

								if (sender->ID == "tank") {
									PvP_Tanks_Killed[sender->team] += 1;
									PvP_Tanks_Lost[entity.team] += 1;
								}

							}
							for (int j = 0; j < 4; j++) { // Spawn particles
								SpawnParticle(pos, 1, 4, 1, .5, col);
							}
							//---- Sound Effects ----//
							if (GameScreenRect.contains(pos)) { laserhit01.play(); }
						}
					}
				}
			}

		}
	}

	void draw() 
	{
		if (eventLogging) { std::cout << "Laser.draw()"; }
		sf::Vector2f G_pos = { pos.x - Camera_Pos[0],pos.y - Camera_Pos[1] };

		//drawCircle(window, {G_pos.x + 1, G_pos.y + 1}, 2, dimCol(col, 25), 1);
		float ratio = life * 2 * 255 / max_life;
		if (ratio > 255) { ratio = 255; }
		if (ratio < 0) { ratio = 0; }

		
		actual_col.a = (sf::Uint8)ratio;

		//drawCircle(window, G_pos, 2, n_col, 1);
		drawThickLine(window, G_pos, G_pos - size[1]*(vel), size[0], actual_col);

		if (eventLogging) { std::cout << "  Laser Drawn" << std::endl; }


		// Draw Particles
		if (sender_ID == "tank") {
			if (rand() % 100 <= 20 * GameFPSRatio) {
				SpawnParticle(pos, 2, .1, 2, 1, col);
			}
		}
		else if (sender_ID == "fort") {
			if (rand() % 100 <= 33 * GameFPSRatio) {
				SpawnParticle(pos, 2, .1, 2, 1, col);
			}
		}
	}
};



class Missle
{
private:

public:
	bool ia;
	sf::Vector2f pos, lpos, vel, acc;
	int id;
	float dam; 
	int no_of_proj;
	float life;
	Entity* target;
	Entity* sender;
	std::vector <sf::Vector2f> last_pos;
	int team;
	sf::Color col;
	float size;
	int trail_length;
	float max_life;
	float ang;
	float splash_radius;

	float terminal_vel, power;

	sf::CircleShape projectile;
	int senderID, targetID, senderteam;
	std::string target_StringID, sender_StringID;

	Missle()
	{
		ia = false;
		trail_length = 10;
		max_life = 180;
	}

	~Missle() {}

	void spawn(sf::Vector2f sp_pos, sf::Vector2f sp_vel, float sp_dam, int sp_no_of_proj, int sp_team, Entity* sp_sender, Entity* sp_target, float sp_size, int sp_trail_length, float sp_splash_radius, float sp_terminal_vel, float sp_power)
	{
		// Needed to prevent bugs and crashes
		if (sp_team < 0 or sp_team >= numberOfTeams) { return; }
		if (sp_target == nullptr) { return; }
		if (sp_sender == nullptr) { return; }


		ia = true;

		dam = sp_dam;
		no_of_proj = sp_no_of_proj;
		pos = sp_pos;
		lpos = pos;
		vel = sp_vel;
		team = sp_team;
		col = colorArr[team];

		sender = sp_sender;
		senderteam = sender->team;
		senderID = sender->uniqueID;


		life = max_life;

		target = sp_target;
		targetID = target->uniqueID;
		target_StringID = target->ID;

		trail_length = sp_trail_length;
		splash_radius = sp_splash_radius;
		size = sp_size;

		projectile.setRadius(size);
		projectile.setOrigin({ size, size });
		projectile.setPointCount(3);
		projectile.setOutlineThickness(1);

		terminal_vel = sp_terminal_vel;
		power = sp_power;

	}

	void draw()
	{
		
		

		float ratio;
		sf::Vector2f t_pos, t_pos2;
		sf::Color t_col;

		// Draw Missle Trail

		if (last_pos.size() > 1) {
			for (int i = 0; i < last_pos.size() - 1; i++) {
				t_pos = last_pos[i];
				t_pos2 = last_pos[i + 1];

				ratio = (i / trail_length) * 192;
				t_col = col;
				t_col.a = ratio + 63;

				t_pos -= {Camera_Pos[0], Camera_Pos[1]}; t_pos2 -= {Camera_Pos[0], Camera_Pos[1]};
				drawThickLine(window, t_pos, t_pos2, size/2, t_col);
			}
		}

		// Draw Missle Projectile
		ratio = life * 2 * 255 / max_life;
		if (ratio > 255) { ratio = 255; }
		if (ratio < 0) { ratio = 0; }

		t_col = this->col;
		t_col.a = ratio;

		
		projectile.setFillColor(t_col);
		t_col = dimCol(t_col, 25);
		t_col.a = ratio;
		projectile.setOutlineColor(t_col);
		projectile.move({ -Camera_Pos[0], -Camera_Pos[1] });
		projectile.setRotation(ang - 30);

		window.draw(projectile);
		projectile.move({ Camera_Pos[0], Camera_Pos[1] });
		

	}

	void move()
	{

		life -= GameFPSRatio;
		if (life <= 0) { ia = false; }
		if (!ia) { explode(); return; }


		// Checking to see if Target is still valid
		__try {
			volatile int dummy = target->uniqueID;
		}__except(EXCEPTION_EXECUTE_HANDLER){
			target = nullptr;
			std::cout << "Error caught at line 2558" << std::endl;
		}

		if (target == nullptr || target->uniqueID != targetID || target->ID != target_StringID) {
			bool found = false;
			for (int i = 0; i < EntityArr.size(); i++) {
				if (EntityArr[i].uniqueID == targetID && target_StringID == EntityArr[i].ID) {
					target = &EntityArr[i];
					found = true;
				}
			}
			if (!found) {
				target = nullptr;
				float lowest_distance = -1;
				float distance, dx, dy;
				for (int i = 0; i < EntityArr.size(); i++) {
					if (EntityArr[i].team != team && EntityArr[i].ID == "tank" && EntityArr[i].ia) {
						dx = pos.x - EntityArr[i].pos[0]; dy = pos.y - EntityArr[i].pos[1];
						distance = std::sqrt(dx * dx + dy * dy);
						if (distance < lowest_distance || lowest_distance == -1) { 
							lowest_distance = distance;
							target = &EntityArr[i];
							targetID = EntityArr[i].uniqueID;
							target_StringID = EntityArr[i].ID;
						}
						// Give Idle Missle New Target
						
					}
				}
			}
		}

		__try {
			volatile int dummy = sender->uniqueID;  // Attempt to access a member.
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			sender = nullptr;
			std::cout << "Error caught at Line:2594" << std::endl;
		}

		if (sender == nullptr || sender->uniqueID != senderID) {
			bool found = false;
			for (int i = 0; i < EntityArr.size(); i++) {
				if (EntityArr[i].uniqueID == senderID) {
					sender = &EntityArr[i];
					found = true;
				}
			}
			if (!found) {
				sender = nullptr;
				bool found2 = false;

				for (int i = 0; i < EntityArr.size(); i++) {
					if (EntityArr[i].ID == sender_StringID && senderteam == EntityArr[i].team) {
						sender = &EntityArr[i];
						senderID = EntityArr[i].uniqueID;
						found2 = true; break;
					}
				}

				if (!found2) {
					ia = false;
					return;
				}

			}
		}



		float dx, dy, t_ang, t_vel, ratio;
		float disx, disy;
		sf::Vector2f l_pos;


		// Limit speed of Missle
		dx = vel.x; dy = vel.y;

		if (abs(dy) < .0001) {
			if (dy >= 0) { dy = .0001; }
			else { dy = -.0001; }
		}

		t_ang = 360 - (atan(dx / dy) * 180 / std::numbers::pi);

		if (dy <= 0) { ang = t_ang - 90; }
		else { ang = t_ang + 90; }

		t_vel = std::sqrt(vel.x * vel.x + vel.y * vel.y);
		
		if (t_vel == 0) { t_vel = .1; }

		ratio = terminal_vel / t_vel;
		if (t_vel > terminal_vel) {
			vel *= ratio;
		}

		// Check Life
		if (life <= 0) { ia = false; explode(); return; }
		


		// Update Trail
		if (last_pos.size() < trail_length) {
			last_pos.push_back(pos);
		}
		else {
			for (int i = 0; i < last_pos.size() - 1; i++) {
				last_pos[i] = last_pos[i + 1];
			}
			last_pos[last_pos.size() - 1] = pos;
		}

		// Move Missle
		if (target != nullptr) {
			disx = abs(pos.x - target->pos[0]);
			disy = abs(pos.y - target->pos[1]);

			if (pos.x < target->pos[0])	{ acc.x = .05 * std::sqrt(disx) * power; }
			else if (pos.x > target->pos[0]) { acc.x = -.05 * std::sqrt(disx) * power; }

			if (pos.y < target->pos[1]) { acc.y = .05 * std::sqrt(disy) * power; }
			else if (pos.y > target->pos[1]) { acc.y = -.05 * std::sqrt(disy) * power; }
		}

		

		lpos = pos;
		vel += acc * GameFPSRatio;
		pos += vel * GameFPSRatio;

		projectile.setPosition(pos);

		// Draw Particles
		if (rand() % 100 <= 25 * GameFPSRatio) {
			SpawnParticle(pos, 3, 1, 2, 1, col);
			SpawnParticle(pos, 3, 1, 2, 1, oppCol(col));
		}

		// Check Collisions
		for (int i = 0; i < EntityArr.size(); i++) {
			if (EntityArr[i].ia && EntityArr[i].team != team) {
				if (FORTS_ATTACK_FORTS || sender->ID != "fort" || EntityArr[i].ID == "tank") {
					if (checkLineCollision(EntityArr[i].collisionRect(), pos, lpos)) {
						
						ia = false;
						explode();

						//---- Sound Effects ----//
						
					}
				}
			}
		}

	}

	void explode()
	{
		if (sender == nullptr) { ia = false; return; }
		for (int i = 0; i < no_of_proj; i++) {
			SpawnLaser(pos.x, pos.y, (splash_radius * .75) + ((rand() % 25) * splash_radius / 100), rand() % 360, dam, team, sender, {5, 1});
		}
	}

	
	

	


};



void Entity::AI()
{
	if (ID == "tank")
	{
		// Event Logging for Troubleshooting
		if (eventLogging) {
			std::cout << std::endl;
			std::cout << "Tank.AI(); GameTick: " << game_ticks << std::endl;
			std::cout << "  Tank ID: " << uniqueID << "  Tank Pos: " << pos[0] << "," << pos[1] << std::endl;
			std::cout << "  lockTarget Timer: " << lock_target_timer << "; no_ammo: " << no_ammo << std::endl;
			if (enemy != nullptr) {
				std::cout << "  Enemy ID: " << enemy->uniqueID << "; Enemy Pos: " << enemy->pos[0] << "," << enemy->pos[1] << std::endl;
			}
		}

		// If Invalid Pointer
		if (enemy != nullptr) {
			bool is_valid = false;
			for (auto& entity : EntityArr) {
				if (&entity == enemy) { is_valid = true; break; }
			}
			if (!is_valid) {
				enemy = nullptr;
			}
		}
		if (enemy != nullptr) {
			if (enemy->uniqueID != enemy_uID) {
				if (eventLogging) { std::cout << "  Target and Enemy object are misaligned" << std::endl; }
				enemy = nullptr;


				for (int i = 0; i < EntityArr.size(); i++) {
					if (EntityArr[i].uniqueID == enemy_uID) {
						if (EntityArr[i].team != team) {
							enemy = &EntityArr[i];
							if (eventLogging) { std::cout << "    Enemy Target found using uID" << std::endl; }
						}
					}
				}

				if (enemy == nullptr) { enemy_uID = -1; }
			}
		}

		// If Invalid Pointer
		// Validate ammo_Target before dereferencing
		if (ammo_Target != nullptr) {
			// Search for the corresponding entity in EntityArr to verify validity
			bool isValid = false;
			for (auto& entity : EntityArr) {
				if (entity.uniqueID == ammo_Target_uID) {
					isValid = true; // Found a matching entity
					ammo_Target = &entity;
					break;
				}
			}

			if (!isValid) {
				// Reset the pointer and ID if invalid
				ammo_Target = nullptr;
				ammo_Target_uID = -1;
				if (eventLogging) {
					std::cout << "  ammo_Target pointer was invalid and has been reset." << std::endl;
				}
			}
		}

		// Proceed with the original logic only if ammo_Target is confirmed valid
		if (ammo_Target != nullptr) {
			if (ammo_Target->uniqueID != ammo_Target_uID && no_ammo && ammo_Target_uID != -1) {
				if (eventLogging) { std::cout << "  Ammo target missing! Realigning..." << std::endl; }
				ammo_Target = nullptr;

				for (auto& entity : EntityArr) {
					if (entity.uniqueID == ammo_Target_uID &&
						entity.ID == "fort" &&
						entity.team == team) {
						ammo_Target = &entity;
						if (eventLogging) { std::cout << "    Ammo Target found using uID" << std::endl; }
						break;
					}
				}

				if (ammo_Target == nullptr) {
					ammo_Target_uID = -1;
					if (eventLogging) {
						std::cout << "    Ammo target not found in EntityArr." << std::endl;
					}
				}
			}
		}





		age += GameFPSRatio;

		// Tanks with Kills get Perks
		if (((kill_count >= kill_count_threshold && kill_count_threshold != -1) ||
			(age >= old_age && old_age != -1)) && level == 0) { // If Tank is old enough or has enough kills, give it a level up
			if (level == 0 && SPECIAL_TANKS) { // if tank has not been upgraded yet
				max_ammo_supply = Tank_MAX_AMMO * special_tank_ammo_factor;  // Increase Max Ammo
				max_hp = Tank_HP * special_tank_hitpoints_factor;	// Increase Max HP
				dam = Tank_DAMAGE * special_tank_damage_factor;		// Increase Damage
				range = Tank_RANGE * special_tank_range_factor;		// Increase Range
				level = 1;											
			}

		}

		if (level != 0 && SPECIAL_TANKS) {
			switch (level)
			{
			case 1:
				if (!no_ammo) { hp += (max_hp * GameFPSRatio * special_tank_healing_factor / 100) / 60; }	// Heal Special Tank
				if (hp > max_hp) { hp = max_hp; }															// Prevent Overhealing
				break;
			}
		}

		// Check Tank Ammo situation
		if ((ammo_supply <= 0 || hp <= max_hp * PanicHealthPerc) && NEED_SUPPLIES) {
			if (!no_ammo) { // If Tank JUST lost all ammo or health reaches critical
				for (int i = 0; i < 10; i++) {
					SpawnParticle({ pos[0], pos[1] }, 4, 2, 2, .5, col);
				}
			}
			no_ammo = true;
		}


		// Tank Death Conditions
		if (hp <= 0) {
			// spawn a dead tank
			SpawnDeadTank({ pos[0],pos[1] }, ang, team);

			ia = false;
			for (int i = 0; i < 10; i++) {		// Spawn Particles
				SpawnParticle({ pos[0], pos[1] }, 8, .5, 2, 1.5, col);
				for (int j = 0; j < 2; j++) {
					// draw more particles
					SpawnParticle({ pos[0], pos[1] }, 3, 1.2, 1, .8, col);
					SpawnParticle({ pos[0], pos[1] }, 3, 2, 1, .8, oppCol(col));
				}
			}



			// Reward Killer
			if (last_bullet_sender != nullptr)
			{
				last_bullet_sender->kill_count += 1;	// Increate killer killcount
				last_bullet_ID = last_bullet_sender->ID;	// Check if bullet came from Tank or Fort
				last_bullet_team = last_bullet_sender->team; // Check team of killer
			}
			else {
				if (eventLogging) { std::cout << "  Last Bullet Sender is NULL" << std::endl; }
			}

			// Convert Tanks if Fort shoots
			if (last_bullet_ID == "fort" && CONVERT_TANKS) {
				int newteam = last_bullet_team;
				team = newteam;
				ia = true;
				hp = max_hp;
				ammo_supply = 0;
			}

			// Update Team Stats
			Tanks_Lost[team] += 1;
			Tanks_Killed[last_bullet_team] += 1;

			// If Tank vs Tank
			if (last_bullet_ID == "tank") {
				quitGame = true;
				PvP_Tanks_Killed[last_bullet_team] += 1;
				PvP_Tanks_Killed[team] += 1;
			}




			int i = rand() % 2;
			// ----- play sound -------
			if (GameScreenRect.contains({ pos[0], pos[1] })) {
				if (rand() % 2 == 0) { tankdies01.play(); }
				else { tankdies02.play(); }
			}
			// ------ play sound end ------------

		}

		if (laser_cooldown > 0) { laser_cooldown -= GameFPSRatio; }


		// Calculate Tank Hitbox
		rect.left = pos[0] - rect.width / 2;
		rect.top = pos[1] - rect.height / 2;


		// Set Target coords
		if (!no_ammo) {
			if (wander_time > 0) {
				wander_time -= GameFPSRatio;
				target_pos = wander_pos;	// Set target position as wander position
				if (eventLogging) {
					std::cout << "  Tank Target changed to wander position" << std::endl;
				}

			}
			else {
				if (idle) {
					wander_time = max_wander_time;
				}
				else {
					if (enemy != nullptr) {
						target_pos.x = enemy->pos[0]; target_pos.y = enemy->pos[1];
						if (eventLogging) {
							std::cout << "  Tank Target changed to enemy position; Pos :" << enemy->pos[0] << "," << enemy->pos[1] << std::endl;
						}
					}
					else {
						if (eventLogging) { std::cout << "  Enemy pointer is NULL" << std::endl; }
						target_pos = { pos[0], pos[1] };

					}



				}
			}
		}
		else {
			ammo_supply_timer -= GameFPSRatio;
		}


		// Look for Ammo Supply (Nearest Friendly Fort)
		if (no_ammo && ammo_supply_timer <= 0) {	// If tank is retreating and the Ammo supply timer is refreshed
			if (eventLogging) { std::cout << "  Tank is searching for nearest valid Fort..." << std::endl; }
			enemy = nullptr; enemy_uID = -1;	// Nullify Enemy Pointers
			target_pos = { pos[0], pos[1] };	// Reset target position
			ammo_supply_timer = max_ammo_supply_time;	// Restart Ammo supply timer
			int lowest_dis = 100000; bool unit_found = false;	// Variables for searching for new Fort, unit_found is True if at least one Fort is available
			int final_unit_index; std::string UnitId;				// Variables for searching for new Fort

			// Iterating through the Entity array to find the closest friendly available Fort
			for (int i = 0; i < EntityArr.size(); i++) {
				// The Last Condition makes it so a Fort freshly captured cannot supply ammo for a brief period
				if (EntityArr[i].team == team && EntityArr[i].ia && EntityArr[i].ID == "fort" && EntityArr[i].Tank_spawn_timer > -(fort_assimilation_ticks - fort_validhealer_ticks)) {
					if (eventLogging) { std::cout << "    Checking Fort ID:" + std::to_string(EntityArr[i].uniqueID) + "..." << std::endl; }


					// Forts have a waiting list, first check if Fort is not already fully booked
					if (!(EntityArr[i].HealTankArray.size() < maxTankHealArray)) { // If Fort is overburdened with Healing Tanks
						if (eventLogging) {
							std::cout << "    Fort Healing Tank Array is full, checking if Tank is on the List..." << std::endl;
							std::cout << "    Fort Healing List [";
							for (int k = 0; k < EntityArr[i].HealTankArray.size(); k++) {
								std::cout << std::to_string(EntityArr[i].HealTankArray[k]);
								if (k < EntityArr[i].HealTankArray.size() - 1) { std::cout << ","; }
							}
							std::cout << "]" << std::endl;
						}

						for (int j = 0; j < EntityArr[i].HealTankArray.size(); j++) {  // Check if Tank is on List

							if (uniqueID == EntityArr[i].HealTankArray[j]) {
								final_unit_index = i;
								unit_found = true;
								ammo_Target = &EntityArr[i];
								ammo_Target_uID = EntityArr[i].uniqueID;
								if (eventLogging) {
									std::cout << "      Tank is on the List" << std::endl;
								}
								break;
							}
						}
						if (eventLogging && !unit_found) { std::cout << "      Tank is not on List" << std::endl; }
					}
					else {	// If the Fort has space, then measure distance and compare with other available forts
						int dx = EntityArr[i].pos[0] - pos[0];
						int dy = EntityArr[i].pos[1] - pos[1];
						double _dis = std::sqrt(dx * dx + dy * dy);
						if (_dis < lowest_dis) {
							lowest_dis = _dis;
							final_unit_index = i;
							unit_found = true;
							ammo_Target = &EntityArr[i];
							ammo_Target_uID = EntityArr[i].uniqueID;
						}
					}

				}
			}


			if (unit_found) {	// At least one Fort was found
				// Add Tank to Healing List
				bool already_in_list = false;
				for (int j = 0; j < EntityArr[final_unit_index].HealTankArray.size(); j++) {	// Iterate through Fort booking list
					if (EntityArr[final_unit_index].HealTankArray[j] == uniqueID) {				// Check if Tank has already booked the Fort
						already_in_list = true;
					}
				}
				if (!already_in_list) { EntityArr[final_unit_index].HealTankArray.push_back(uniqueID); } // Book Tank to Fort if not already booked, to prevent tanks from booking twice


				if (eventLogging) {
					std::cout << "    Ammo Target found" << std::endl;
					std::cout << "    Ammo Target ID: " << ammo_Target->uniqueID << std::endl;
					target_pos = { ammo_Target->pos[0], ammo_Target->pos[1] };

				}

			}
			else {	// No available forts, either all Forts are booked, assimilating or non-existant
				if (eventLogging) { std::cout << "    Ammo Target not found" << std::endl; }
				ammo_Target = nullptr;	// No ammo target, set to NULL to avoid memory error
				idle = true;			// Tank is set to Idle, consequences unknown 
				ammo_Target_uID = -1;
			}
		}





		//--------------- Calculate Enemy Tank Angle --------------------
		// Calculating target angle
		if (no_ammo) {	// If Tank is retreating
			if (!idle) {	// If tank is retreating and not idle (so Tank therefore has an Ammotarget)
				if (ammo_Target != nullptr) {	// Confirm ammotarget is not NULL
					target_pos.x = ammo_Target->pos[0]; target_pos.y = ammo_Target->pos[1];		// Set Tank target position as the position of Ammo target
					if (eventLogging) { std::cout << "  Tank Target changed to ammunition target" << std::endl; }
				}
				else {	// Tank is retreating and not idle but has no ammo target?
					if (eventLogging) { std::cout << "  ammo_Target is NULL"; }
					target_pos = { pos[0], pos[1] };
					idle = true;
					ammo_Target_uID = -1;
				}

			}
			else {
				if (eventLogging) { std::cout << "  Tank is idle, tank target is now {0,0}" << std::endl; }
			}
		}


		float dx = target_pos.x - pos[0];
		float dy = target_pos.y - pos[1];

		// Prevent division by zero
		if (abs(dy) < .0001) {
			dy = (dy >= 0) ? .0001 : -.0001;
		}

		double t_ang = 360 - (atan(dx / dy) * 180 / std::numbers::pi);

		if (dy <= 0) {
			targ_ang = t_ang - 90;
		}
		else {
			targ_ang = t_ang + 90;
		}

		// Normalize angles to the range [0, 360)
		while (ang < 0) { ang += 360; }
		while (ang >= 360) { ang -= 360; }

		while (targ_ang < 0) { targ_ang += 360; }
		while (targ_ang >= 360) { targ_ang -= 360; }



		// Rotate tank
		if (abs(targ_ang - ang) > 1.5) {
			if (targ_ang > ang) {
				if (abs(targ_ang - ang) < 180) {
					tilt(1);
				}
				else {
					tilt(-1);
				}
			}
			else {
				if (abs(targ_ang - ang) < 180) {
					tilt(-1);
				}
				else {
					tilt(1);
				}
			}
		}
		else {
			deccelAng();
		}

		///////////////// TANK MOVEMENT /////////////////////
		dx = target_pos.x - pos[0];
		dy = target_pos.y - pos[1];

		if (dy == 0) {
			int x = rand() % 2;
			switch (x) {
			case 0:
				dy = -.1;
				break;
			case 1:
				dy = .1;
				break;
			}
		}

		double dis = std::sqrt(dx * dx + dy * dy);
		float tankspeed;
		// Tanks with less ammo move faster/slower
		if (SHINYS_MOVE_FAST) { tankspeed = 1 + (ammo_supply / max_ammo_supply); }
		else { tankspeed = 2 - (ammo_supply / max_ammo_supply); }



		if (SPECIAL_TANKS && level != 0) { tankspeed *= special_tank_speed_factor; } // Special tanks move faster

		if (dis > range && !no_ammo) {
			if (abs(targ_ang - ang) > 180) {
				if (dx > 0) { accel(tankspeed); }
				else { accel(-tankspeed); }
			}
			else {
				accel(tankspeed);
			}
		}
		else {
			if (!no_ammo) { deccel(); }
		}

		// Don't deccelerate while resupplying ammo

		if (no_ammo) {
			// HP affects Tank Speed
			if (DAMAGED_MOVE_FAST) { tankspeed = 2 - (hp / max_hp); }
			else { tankspeed = 1 + (hp / max_hp); }

			if (abs(targ_ang - ang) > 180) {
				if (dx > 0)
					accel(tankspeed);
				else
					accel(-tankspeed);
			}
			else {
				accel(tankspeed);
			}
		}
		move();

		// Reload ammo/heal tank
		if (no_ammo) {

			if (ammo_Target != nullptr) {
				bool target_found = false;
				for (Entity &entity : EntityArr) {
					if (entity.uniqueID == ammo_Target_uID) {
						target_found = true;
						ammo_Target = &entity;
						target_pos = { entity.pos[0] , entity.pos[1] };
						dx = pos[0] - entity.pos[0];
						dy = pos[1] - entity.pos[1];
						dis = std::sqrt(dx * dx + dy * dy);
					}
				}
				if (!target_found) {
					ammo_Target = nullptr;
				}
			}
			if (ammo_Target != nullptr) {
				if (dis < ammo_Target->range / 20 && ammo_Target->ia) { // If Tank is close enough to Fort and Fort is still valid
					deccel();	// decelerate Tank

					if (hp < max_hp) {
						hp += max_hp / 25;	// Heal Tank by 4% of max HP per frame
					}
					else {
						// Heal Fort
						ammo_Target->fort_tanks_healed += 1; // Increment Fort's healed tanks counter

						if (ammo_Target->hp < ammo_Target->max_hp && FORT_HEALING) { // If Fort is not at max HP and healing is enabled
							if (ammo_Target->fort_level == 1) { ammo_Target->hp += ammo_Target->max_hp * tank_fort_heal_percent * 0.05; } // If Fort is a special fort, don't heal as much
							else if (ammo_Target->fort_level == 0) { ammo_Target->hp += ammo_Target->max_hp * tank_fort_heal_percent; } // If Fort is a normal fort, heal
							

							if (ammo_Target->hp > ammo_Target->max_hp) {
								ammo_Target->hp = ammo_Target->max_hp; // prevent overhealing
							}
						}

						// Finished Reloading Ammo
						no_ammo = false;  // Reset no_ammo boolean
						ammo_supply = max_ammo_supply;	// Reset ammo supply to max
						hp = max_hp;	// Reset HP to max HP
						

						// Sound and Particle Effects
						if (GameScreenRect.contains({ pos[0], pos[1] })) {
							tankreload01.play();
							for (int i = 0; i < 5; i++) {
								SpawnParticle({ pos[0], pos[1] }, 3, 2, 2, 1, col);
								SpawnParticle({ pos[0], pos[1] }, 3, 2, 2, 1, oppCol(col));
							}
						}

					}
				}
			}
			else {
				if (eventLogging) { std::cout << "  Ammo Target is null" << std::endl; }
			}

		}


		/////////////////////  S H O O T  /////////////////////
		if (abs(targ_ang - ang) <= 7.5 && !idle && laser_cooldown <= 0 && dis <= range && !no_ammo) {
			sf::Vector2f laser_pos(pos[0], pos[1]);

			float x = cos(ang * std::numbers::pi / 180) * rect.height / 2;
			float y = sin(ang * std::numbers::pi / 180) * rect.height / 2;
			laser_pos.x += x; laser_pos.y += y;

			// Spawn Projectile to shoot
			if (ammo_supply <= Tank_MISSLE_NO) {
				SpawnMissle(laser_pos, tank_missle_velocity, ang, dam * tank_missle_damagefactor, tank_missle_projectile_no, 
							team, this, enemy, Tank_Missle_Size, Tank_Missle_TrailLength, tank_missle_splash_radius, 
							tank_missle_terminal_velocity, tank_missle_power); // spawn missle
				if (eventLogging) { std::cout << "  Missle shot" << std::endl; }
			}
			else {

				SpawnLaser(laser_pos.x, laser_pos.y, 12.5, ang, dam, team, this, { 4, .66 }); // spawn laser
				if (eventLogging) { std::cout << "  Laser shot" << std::endl; }
			}

			ammo_supply -= 1;  // Decrease ammo supply
			laser_cooldown = max_laser_cooldown;  // Reset laser cooldown


			// ------- Particles Go Here ----------------
			for (int i = 0; i < 8; i++) {
				SpawnParticle(laser_pos, 4, .45, 2, 1, oppCol(col));
			}

			// --------- Sound Effects Go Here -----------
			if (GameScreenRect.contains({ pos[0], pos[1] })) {
				if (rand() % 2 == 0) { tankshoot01.play(); }
				else { tankshoot02.play(); }
			}


		}


		if (eventLogging) {
			std::cout << "	Entity Variables" << std::endl;
			std::cout << "		Ammo Target ID:" << ammo_Target->uniqueID << std::endl;
			std::cout << "		Idle:" << idle << std::endl;

		}

	}

	if (ID == "fort")
	{
		// Event Logging for debugging
		if (eventLogging) {
			std::cout << std::endl;
			std::cout << "Fort.AI(); GameTick: " << game_ticks << std::endl;
			std::cout << "  Fort ID: " << uniqueID << "  Fort Pos: " << pos[0] << "," << pos[1] << std::endl;
			std::cout << "  Fort Angles; ang = " << ang << "; targ_ang = " << targ_ang << std::endl;
			if (enemy != nullptr) {
				std::cout << "  Enemy ID: " << enemy->uniqueID << "; Enemy Pos: " << enemy->pos[0] << "," << enemy->pos[1] << std::endl;
			}
			std::cout << "  Healing Tanks Array: [";
			for (int i = 0; i < HealTankArray.size(); i++) {
				std::cout << std::to_string(HealTankArray[i]);
				if (i < HealTankArray.size() - 1) {
					std::cout << ",";
				}
			}
			std::cout << "]" << std::endl;
		}

		// If enemy is a null pointer
		if (enemy != nullptr) {
			bool is_valid = false;
			for (auto& entity : EntityArr) {
				if (&entity == enemy) {
					is_valid = true;
					break;
				}
			}
			if (!is_valid) {
				enemy = nullptr;
			}
		}

		if (enemy != nullptr) {
			if (enemy->uniqueID != enemy_uID) {
				if (eventLogging) { std::cout << "  Target and Enemy object are misaligned" << std::endl; }
				enemy = nullptr;

				// Search for the enemy in EntityArr using uniqueID
				for (Entity &entity : EntityArr) {
					if (entity.uniqueID == enemy_uID) {
						enemy = &entity;
						if (eventLogging) { std::cout << "    target found" << std::endl; }
					}
				}

				if (enemy == nullptr) { enemy_uID = -1; }
			}
		}


		// Update Tank Healing Array
		
		if (game_ticks % 30 == 0) {
			HealTankArray.clear();
		}



		float temp_ang;
		float x, y;
		
		// Code to upgrade Fort
		if (((fort_tanks_spawned >= fort_tanks_spawned_threshold && fort_tanks_spawned_threshold != -1) ||
			(fort_tanks_healed >= fort_tanks_healed_threshold && fort_tanks_healed_threshold != -1))
			&& SPECIAL_FORTS) { // Checking the requirements for Special Forts [If Fort has healed or spawned enough tanks]
			if (special) {
				if (fort_level == 0) { // If fort JUST leveled up
					for (int i = 0; i < 15; i++) {
						SpawnParticle({ pos[0], pos[1] }, 8, 2, 2, .5, col);
					}

					max_missle_cooldown = max_laser_cooldown * 33 / special_fort_misslecooldown_factor; // Fort shoots missles more frequently
					max_hp = Fort_HP * special_fort_hitpoints_factor; // Fort Max Health increased
					hp = max_hp;
					max_Tank_spawn_time = Fort_SPAWNTANK_TIME / special_fort_tankspawn_factor; // Fort spawns tanks faster
					range = Fort_RANGE * special_fort_range_factor; // Fort Range increased

				}
				fort_level = 1;
			}
			else {
				special = true;
				fort_tanks_healed = fort_tanks_healed_threshold;
				fort_tanks_spawned = fort_tanks_spawned_threshold;

				// Apply special fort properties
				max_missle_cooldown = max_laser_cooldown * 33 / special_fort_misslecooldown_factor;
				max_hp = Fort_HP * special_fort_hitpoints_factor;
				hp = max_hp;
				max_Tank_spawn_time = Fort_SPAWNTANK_TIME / special_fort_tankspawn_factor;
				range = Fort_RANGE * special_fort_range_factor;

				fort_level = 1; // Mark as leveled up
			}

		}

		switch (fort_level) // Fort Level Upgrades (currently only two levels, 0 and 1)
		{
		case 1:
			if (hp < max_hp) {
				hp += max_hp * GameFPSRatio / ((100 / special_fort_healing_factor) * 60); // Special Fort Healing
			}
			if (hp > max_hp) { hp = max_hp; }

			break;
		default:
			break;
		}




		// When the Fort is destroyed
		if (hp <= 0) {
			if (eventLogging) { std::cout << "  Fort Captured" << std::endl; }

			// Change the team of the current Fort
			if (CONVERT_FORTS) {
				int newteam = last_bullet_team;

				// Update the team and color
				team = newteam;
				col = colorArr[newteam];
				opp_col = oppCol(col);

				// Reset assimilation timer
				Tank_spawn_timer = -fort_assimilation_ticks;

				// Reset healing and spawning stats
				fort_tanks_healed = 0;
				fort_tanks_spawned = 0;

				fort_level = 0; // GET BACK HERE

				// Reset all Fort Stats from special fort
				max_missle_cooldown = max_laser_cooldown * 33 * fort_missle_cooldown_factor;
				max_hp = Fort_HP;
				hp = max_hp;
				max_Tank_spawn_time = Fort_SPAWNTANK_TIME;
				range = Fort_RANGE;
				special = false;
				level = 0;


				// Flash effect to indicate capture
				for (int i = 0; i < 40; i++) {
					SpawnParticle({ pos[0], pos[1] }, 15, 4, 2, .8, colorArr[newteam]);
				}

				// Gift tanks if enabled
				if (GIFT_TANKS) {
					for (int i = 0; i < 2; i++) {
						float x = (rand() % 10) - 5 + pos[0];
						float y = (rand() % 10) - 5 + pos[1];
						SpawnTank({ x, y }, newteam);
					}
				}

				// Play sound effect
				if (GameScreenRect.contains({ pos[0], pos[1] })) {
					fortcaptured01.play();
				}
			}

			// Update team stats
			Forts_Lost[team] += 1;
			Forts_Destroyed[last_bullet_team] += 1;

			// Reset health for the new team
			hp = max_hp;
		}


		if (hp <= max_hp * .5) {
			float FACTOR = (.5 - (hp / max_hp)) * 2 * 5;

			if (rand() % 100 <= 10 * FACTOR) {
				SpawnParticle({ pos[0], pos[1] }, 4, 1.5, 2, .5, oppCol(col));
			}
			if (rand() % 100 <= 2 * FACTOR) {
				for (int i = 0; i < 5; i++) {
					SpawnParticle({ pos[0], pos[1] }, 3, 3, 1, .8, oppCol(col));
				}
			}
		}

		if (laser_cooldown > 0) { laser_cooldown -= GameFPSRatio; }
		if (missle_cooldown > 0) { missle_cooldown -= GameFPSRatio; }

		// Spawn Tanks from Forts
		Tank_spawn_timer += GameFPSRatio;
		if (Tank_spawn_timer >= max_Tank_spawn_time) {
			if (eventLogging) { std::cout << "  Fort Spawns Tank" << std::endl; }
			int tank_population = getTankPop(team);
			if (tank_population < Tank_MAX_POP + extra_population && FORTS_SPAWN_TANKS) {
				x = (rand() % 10) - 5; y = (rand() % 10) - 5;
				x += pos[0]; y += pos[1];

				Tank_spawn_timer = 0;

				fort_tanks_spawned += 1;
				for (int i = 0; i < 20; i++) {
					SpawnParticle({ pos[0], pos[1] }, 7.5, 2.25, 2, 1 / 1.5, col);
				}

				if (GameScreenRect.contains({ pos[0], pos[1] })) {
					tankcreated01.play();
				}
				SpawnTank({ x, y }, team);
			}
			else {
				// Pop Cap is reached
				Tank_spawn_timer = max_Tank_spawn_time;
				if (rand() % 100 <= 10 * GameFPSRatio) {
					SpawnParticle({ pos[0], pos[1] }, 5, .75, 2, 2, col);
				}
			}
		}


		if (eventLogging) { std::cout << "  Fort Starts looking for enemies if idle...." << std::endl; }

		
		bool this_is_a_null = false;
		if (this != nullptr) {
			bool is_valid = false;
			for (auto& entity : EntityArr) {
				if (&entity == this) {
					is_valid = true;
					break;
				}
			}
			if (!is_valid) {
				this_is_a_null = true;

			}
		}
		if (this_is_a_null) {
			return;
		}
		
		if (wander_time > 0) { wander_time -= 1; }
		else { lockTarget(); }



		double dis,dx, dy;
		dx = target_pos.x - pos[0]; dy = target_pos.y - pos[1];
		dis = std::sqrt(dx * dx + dy * dy);
		if (eventLogging) { std::cout << "  Fort Target Pos: " << target_pos.x << "," << target_pos.y << std::endl; }

		dx = target_pos.x - pos[0]; dy = target_pos.y - pos[1];
		if (dy == 0) {
			int x = rand() % 2;
			switch (x) {
			case 0:
				dy = -.1;
				break;
			case 1:
				dy = .1;
				break;
			}
		}

		if (dx == 0) {
			int x = rand() % 2;
			switch (x) {
			case 0:
				dx = -.1;
				break;
			case 1:
				dx = .1;
				break;
			}
		}

		if (eventLogging) { std::cout << "  Moving Fort Gun..." << std::endl; }
		temp_ang = 360 - (atan(dx / dy) * 180 / std::numbers::pi);
		if (dy <= 0) {
			targ_ang = temp_ang - 90;
		}
		else {
			targ_ang = temp_ang + 90;
		}

		// Eliminate excess value
		if (eventLogging) { std::cout << "  Fort Angles; ang = " << ang << "; targ_ang = " << targ_ang << std::endl; }
		ang = (int)ang % 360; targ_ang = (int)targ_ang % 360;


		while (ang > 360) { ang -= 360; }
		while (ang < 0) { ang += 360; }
		while (targ_ang > 360) { targ_ang -= 360; }
		while (targ_ang < 0) { targ_ang += 360; }




		// Moving Fort Gun
		if (targ_ang > ang) {
			if (abs(targ_ang - ang) < 180) { tilt(4); }
			else { tilt(-4); }
		}
		else if (targ_ang < ang) {
			if (abs(targ_ang - ang) < 180) { tilt(-4); }
			else { tilt(4); }
		}


		// Move Gun
		v_ang += a_ang * GameFPSRatio;
		ang += v_ang * GameFPSRatio;
		v_ang *= (float)pow(.9, GameFPSRatio);
		a_ang = 0;




		// ##################### S H O O T ########################################

		if (eventLogging) {
			if (idle) { std::cout << "  Fort is Idle" << std::endl; }
			else { std::cout << "  Fort is not Idle" << std::endl; }
		}

		// Shoot Missle
		if (missle_cooldown <= 0 && !FORTS_NEUTERED && Tank_spawn_timer > 0 && FORT_MISSLES) {
			Entity* random_unit;
			std::vector <Entity*> random_unit_arr;
			bool found = false;
			float dx, dy;

			for (int i = 0; i < EntityArr.size(); i++) {
				if (EntityArr[i].team != team && EntityArr[i].ID != "fort") {
					dx = EntityArr[i].pos[0] - pos[0];
					dy = EntityArr[i].pos[1] - pos[1];
					double dis = std::sqrt(dx * dx + dy * dy);
					if (dis <= range * .9) {
						found = true;
						random_unit_arr.push_back(&EntityArr[i]);
					}
				}
			}

			if (found) {
				random_unit = random_unit_arr[rand() % random_unit_arr.size()];
				SpawnMissle({ pos[0], pos[1] }, fort_missle_velocity, ang, Fort_DAMAGE * fort_missle_damagefactor,
					fort_missle_projectile_no, team, this, random_unit, Fort_Missle_Size,
					Fort_Missle_TrailLength, fort_missle_splash_radius, fort_missle_terminal_velocity,
					fort_missle_power);

				missle_cooldown = max_missle_cooldown;
			}
			else if (!idle) {
				SpawnMissle({ pos[0], pos[1] }, fort_missle_velocity, ang, Fort_DAMAGE * fort_missle_damagefactor,
					fort_missle_projectile_no, team, this, enemy, Fort_Missle_Size,
					Fort_Missle_TrailLength, fort_missle_splash_radius, fort_missle_terminal_velocity,
					fort_missle_power);

				missle_cooldown = max_missle_cooldown;
			}


		}



		// Shoot Laser
		if (abs(targ_ang - ang) <= 15 && !idle && laser_cooldown <= 0 && !FORTS_NEUTERED && Tank_spawn_timer > 0) {
			if (eventLogging) {
				std::cout << "  Fort Shoots Laser" << std::endl;
			}

			float x; float y;
			x = gun_barrel[0] * cos(ang * std::numbers::pi / 180) + pos[0];
			y = gun_barrel[0] * sin(ang * std::numbers::pi / 180) + pos[1];

			SpawnLaser(x, y, 20, ang, dam, team, this, { 2, .75 });

			laser_cooldown = max_laser_cooldown;


			// Draw Bullet Particles
			for (int i = 0; i < 5; i++) {
				SpawnParticle({ x, y }, 4, 3, 2, .25, oppCol(col));
			}
			//--- Sound Effects ----//
			if (GameScreenRect.contains({ pos[0], pos[1] })) {
				fortshoot01.play();
			}
		}


	}
}
void Entity::move()
{
	if (ID == "tank") {
		if (eventLogging) { std::cout << "Tank.move(); GameTick: " << game_ticks << std::endl; }

		lock_target_timer += GameFPSRatio;

		if (lock_target_timer >= max_lock_target_time) {
			lock_target_timer = 0;
			if (eventLogging) {
				std::cout << "  lock_target_timer is maxed; checking for new targets" << std::endl;
			}

			if (!no_ammo) { lockTarget(); }
		}
		if ((enemy == nullptr || !enemy->ia) && !idle) {
			if (eventLogging) {
				std::cout << "  enemy is unavailable; finding target..." << std::endl;
			}

			lockTarget();
		}


		// Tank Rotation
		v_ang += a_ang * GameFPSRatio;
		ang += v_ang * GameFPSRatio;
		v_ang *= (float)pow(.92, GameFPSRatio);
		a_ang = 0;

		//last_pos += pos;

		// Add GameFPSRatio
		for (int i = 0; i < 2; i++) {
			vel[i] += acc[i] * GameFPSRatio;
			pos[i] += vel[i] * GameFPSRatio;
			vel[i] *= (float)pow(.9, GameFPSRatio);
		}


		// Update Chunks
		chunk[0] = (pos[0] / 16);
		chunk[1] = (pos[1] / 16);

	}

	if (ID == "fort") {

	}
}
void Entity::draw()
{
	if (ID == "tank") {
		if (eventLogging) { std::cout << "Tank.draw()" << std::endl; }

		

		// Spawn Particles for Damaged tanks
		opp_col.a = 255;
		if ((ammo_supply <= 0 || hp <= max_hp * PanicHealthPerc) && NEED_SUPPLIES) {
			if (rand() % 100 <= 7 * GameFPSRatio) {
				SpawnParticle({ pos[0] , pos[1] }, 2.5, .5, 2, 2, opp_col);
			}
			if (NEED_SUPPLIES)
				no_ammo = true;
		}

		float ratio = hp / max_hp;
		
		// Spawn particles for damaged tanks II
		if ((rand() % 100 <= 25 * (1 - ratio)) && ratio < .67) { for (int i = 0; i < rand() % 4; i++) { SpawnParticle({ pos[0],pos[1] }, 2, 2, 1, .8, opp_col); } }

		float G_pos[2] = { pos[0] - Camera_Pos[0],pos[1] - Camera_Pos[1] };
		col;
		
		col.a = (sf::Uint8)(32 * (ammo_supply / max_ammo_supply));
		opp_col.a = 32;
		if (hp < 0) { col.a = 0; }

		//t_col = oppCol(t_col);
		//t_col.a = 64;

	

		// reused variables
		float tank_circle_radius = TransRangeTank * Tank_RANGE;

		// Draw Tank Sprite and LOS
		drawFilledCircle(window, { G_pos[0], G_pos[1] }, tank_circle_radius * .75, col);

		entitySprite.setOrigin((float)texWidth / 2, (float)texHeight / 2);
		entitySprite.setPosition(G_pos[0], G_pos[1]);
		entitySprite.setRotation(ang + 90);

		window.draw(entitySprite);

		// Draw Health bar/circle
		tank_health_arc_angle += GameFPSRatio * 2;
		float _ang = tank_health_arc_angle;
		drawArc(window, { G_pos[0], G_pos[1] }, tank_circle_radius * .8, opp_col, 3, _ang, _ang + hp * 360 / max_hp, 20);

		// Draw Circle for Special Tanks
		if (level != 0) {
			drawCircle(window, { G_pos[0], G_pos[1] }, tank_circle_radius, col, 3);
			if (rand() % 100 <= 8 * GameFPSRatio) {
				SpawnParticle({ pos[0] , pos[1] }, 3.5, .4, 2, 2.25, col);
			}
		}

		if (DEBUG_FEATURES) {
			col.a = 64;
			drawLine(window, { G_pos[0], G_pos[1] }, { target_pos.x - Camera_Pos[0], target_pos.y - Camera_Pos[1] }, col);

			sf::FloatRect n_rect = collisionRect();
			n_rect.left -= Camera_Pos[0];
			n_rect.top -= Camera_Pos[1];

			col.a = 255.f * (hp / max_hp);
			drawRect(window, n_rect, col, 1);
		}

		if (eventLogging) { std::cout << "  Tank Drawn." << std::endl; }
	}

	if (ID == "fort")
	{
		if (eventLogging) { std::cout << "Fort.draw()" << std::endl; }

		// Fort Assimilation Particles
		opp_col.a = 255;
		if (Tank_spawn_timer < 0) {
			float ratio = (-Tank_spawn_timer / fort_assimilation_ticks);
			ratio = 1 - ratio;

			if (rand() % 100 <= (14 * GameFPSRatio * ratio) + 1) {
				for (int i = 0; i < 2; i++) {
					SpawnParticle({ pos[0], pos[1] }, 3, .5, 2, 1 + (3 * ratio), opp_col);
				}
			}
		}

		
		float x0 = round(pos[0] - Camera_Pos[0]); float y0 = round(pos[1] - Camera_Pos[1]);
		float x1, y1, x2, y2;
		float x, y;
		float ratio;
		float tmp_size;
		
		sf::FloatRect tmp_rect, shadow_rect;

		// Calculate Fort rectangle
		tmp_size = Fort_SIZE;
		if (fort_level != 0) {
			tmp_size = Fort_SIZE * 1.125;
		}
		tmp_rect = { x0 - tmp_size / 2, y0 - tmp_size / 2, tmp_size, tmp_size };



		float flicker_ratio = flicker_timer * 24 / max_flicker_time;
		
		col.a = (sf::Uint8)(flicker_ratio + 8);
		if (draw_transp_fort && Tank_spawn_timer > 0) {

			if (fort_level != 0) {
				drawFilledCircle(window, { x0, y0 }, Fort_RANGE * TransRangeFort * .8, col);
				drawCircle(window, { x0, y0 }, Fort_RANGE * TransRangeFort * 1, col, 4);
			}
			else {
				drawFilledCircle(window, { x0, y0 }, Fort_RANGE * TransRangeFort * .8, col);
			}
		}

		// Draw Health bar
		col.a *= 1.5;  // Health bar is slightly more opaque
		fort_health_arc_angle += GameFPSRatio * .33;
		float _ang = fort_health_arc_angle;
		drawArc(window, { x0, y0 }, Fort_RANGE * TransRangeFort * .88 - 1, col, 5, _ang, _ang + hp * 360 / max_hp, 25);
		col.a /= 1.5; // Reset col.a to original value
		// If fort is assimilating
		if (Tank_spawn_timer < 0) {
			opp_col.a = 24;
			float n_ratio = 1 + (Tank_spawn_timer / (float)fort_assimilation_ticks);

			
			fort_assimilation_arc_angle -= GameFPSRatio * .5;
			_ang = fort_assimilation_arc_angle;
			drawArc(window, { x0,y0 }, Fort_RANGE * TransRangeFort * .75, opp_col, 4, _ang, _ang + 360 * n_ratio, 25);
		}

		// Drawing Fort Gun
		if (!FORTS_NEUTERED) {

			if (fort_level != 0) { // Leveled up Fort has Bigger gun
				gun_barrel[0] = 45;
				gun_barrel[1] = 3;
			}

			x1 = gun_barrel[0] * cos(ang * std::numbers::pi / 180) + pos[0];
			y1 = gun_barrel[0] * sin(ang * std::numbers::pi / 180) + pos[1];
			x1 -= Camera_Pos[0]; y1 -= Camera_Pos[1];

			opp_col.a = 255;
			drawThickLine(window, { x0, y0 }, { x1, y1 }, gun_barrel[1], opp_col);
		}

		float dis;
		float dx = target_pos.x - pos[0]; float dy = target_pos.y - pos[1];
		dis = std::sqrt(dx * dx + dy * dy);


		if (DEBUG_FEATURES) {
			// Draw Debug Features
			if (dis <= range && !idle) {
				x2 = target_pos.x - Camera_Pos[0]; y2 = target_pos.y - Camera_Pos[1];
			}
			
			opp_col.a = (sf::Uint8)(128 * flicker_timer / max_flicker_time);
			if (!idle) {
				drawThickLine(window, { x0, y0 }, { x2, y2 }, 4, opp_col);
			}

			if (HealTankArray.size() >= maxTankHealArray) {
				col.a = 64;
				drawCircle(window, { x0, y0 }, 50, col, 5);
			}
		}




		// Draw Fort Body
		col.a = 255;
		drawFilledRect(window, tmp_rect, col);


		sf::Color dim_col = dimCol(col, 50);
		drawRect(window, tmp_rect, dim_col, 1);

		flicker_timer += flicker_vel;
		if (flicker_timer >= max_flicker_time) {
			flicker_vel = -1;
			flicker_timer - max_flicker_time;
		}
		if (flicker_timer <= 0) {
			flicker_vel = 1;
			flicker_timer = 0;
		}

		ratio = 192 * flicker_timer / max_flicker_time;
		//sf::Color tmp_col;



		// Draw Fort Info
		if (draw_fort_stats && Tank_spawn_timer > 0) {
			float h_size = tmp_size / 2;
			x = pos[0] - tmp_size; y = pos[1] - tmp_size;
			x -= Camera_Pos[0]; y -= Camera_Pos[1];


			ratio = round(Tank_spawn_timer * (tmp_size * 2) / max_Tank_spawn_time);

			y += 5; col.a = 128;
			tmp_rect = { x, y, tmp_size * 2, 2 };

			drawFilledRect(window, tmp_rect, col);
			if (ratio < 0) { ratio = 0; }
			tmp_rect = { x, y, ratio, 2 };

			col.a = 255;
			drawFilledRect(window, tmp_rect, col);
		}



		if (DEBUG_FEATURES) {
			//---- Draw text ----//
		}


	}


	col.a = 255;
	opp_col.a = 255;
}



class Particle
{
public:
	bool ia;
	float timer, max_timer;

	sf::Vector2f pos, vel;
	float size, range;
	sf::Color col;
	int type;

	sf::RectangleShape myRect;
	float windforce;

	

	Particle() 
	{
		ia = true;
		timer = 0; //max_timer = 60;
	}

	void spawn(sf::Vector2f sp_pos, float sp_size, float sp_range, int sp_type, float sp_durRate, sf::Color sp_col) 
	{
		pos = sp_pos;
		size = sp_size;
		range = sp_range;
		type = sp_type;
		col = sp_col;

		float ang = (rand() % 360) * std::numbers::pi / 180;
		float sp_vel = sp_range * (rand() % 100) / 100;
		vel = {cos(ang) * sp_vel, sin(ang) * sp_vel};

		max_timer = DefaultPartTimer * sp_durRate;
		
		timer = max_timer;

		if (type == 2) {
			myRect.setSize({ size, size });
			myRect.setFillColor(sp_col);
		}

		windforce = 0;
		
	}

	void move() 
	{
		if (WIND_Physics) {
			if (type == 2) { vel += wind_vel * GameFPSRatio; } // Wind effects
			sf::Vector2f nWind = wind_vel;
			nWind.x *= .5; nWind.y *= .5;
			if (type == 1) { vel += nWind * GameFPSRatio; }
		}
	
		pos += vel * GameFPSRatio;
		
		timer -= GameFPSRatio;
		if (timer <= 0) {
			ia = false;
		}
	}

	void draw() 
	{
		float x1 = pos.x; float y1 = pos.y;
		float x2 = x1 - vel.x * 2 * size; float y2 = y1 - vel.y * 2 * size;
	
		float ratio = timer * 255 / max_timer;
		if (ratio < 0) { ratio = 0; }

		

		
		col.a = (sf::Uint8)ratio;


		

		switch (type)
		{
		case 1:
			x1 -= Camera_Pos[0]; y1 -= Camera_Pos[1];
			x2 -= Camera_Pos[0]; y2 -= Camera_Pos[1];

			drawLine(window, {x1, y1}, {x2, y2}, col);
			break;
		case 2:
			myRect.setPosition({ pos.x - (size / 2) , pos.y - (size / 2) });
			myRect.setFillColor(col);
			myRect.move({ -Camera_Pos[0], -Camera_Pos[1] });
			window.draw(myRect);
			break;
		}

	}

};



class Tile
{
public:
	sf::Vector2f pos;
	int grid_x, grid_y;
	sf::Color col, opp_col;
	int team;
	int FortID;
	//sf::FloatRect rect;
	float radius;
	Entity* fort;
	sf::CircleShape circle;

	float flash_state, flash_timer, max_flash_time, flash_vel;
	sf::Color flash_col;
	float flash_intensity;
	bool border_tile;

	float flicker_timer, flicker_timer_vel;

	std::vector <Tile*> neighbors;

	int tank_deaths;

	bool fort_is_assimilating;


	Tile(sf::Vector2f sp_pos, int gx, int gy) :
		col({ 0, 0, 0, 0 }), flash_state(false), flash_timer(0), max_flash_time(60),
		flash_vel(1), flash_intensity(255), FortID(-1), pos(sp_pos), team(-1),
		fort(nullptr), radius(0), grid_x(gx), grid_y(gy), border_tile(false), neighbors{},
		flicker_timer(0), flicker_timer_vel(1), tank_deaths(0), fort_is_assimilating(false)
	{
		
		flicker_timer = (float)((rand() % 99 )+ 1) ;
		radius = Tiles_Size / 2;
		circle.setRadius(radius * 1.15);
		circle.setPointCount(6);
		circle.setOutlineThickness((int)(Tiles_Size / 50) + 1);
		circle.setOrigin(Tiles_Size / 2, Tiles_Size / 2);
		circle.setFillColor({ 0,0,0,0 });
		
	}

	void update()
	{

		float dx, dy, dis, smallest_dis;
		bool found = false;
		smallest_dis = Fort_RANGE * 2;
		sf::Color last_col;
		last_col = col;
		

		// Looking for closest fort
		for (Entity &entity : EntityArr) {
			if (entity.ID == "fort") {
				dx = pos.x - entity.pos[0];
				dy = pos.y - entity.pos[1];

				dis = std::sqrt(dx * dx + dy * dy);
				
				if (dis / entity.getTerritoryPower() < smallest_dis && dis / entity.getTerritoryPower() < entity.range * 2) {
					smallest_dis = dis / entity.getTerritoryPower();
					fort = &entity;
					FortID = entity.uniqueID;
					found = true;
				}
			}
		}
		if (found) {
			team = fort->team;
			col = colorArr[team];
			opp_col = oppCol(col);
			col.a = 64;
			fort_is_assimilating = (fort->Tank_spawn_timer < 0);
			if (smallest_dis > fort->range) {
				col.a = 16;
			}
			if(col != last_col && GameScreenRect.contains(pos)){
				flash(Fort_RANGE * 2 / smallest_dis, fort->col, 128);
				if (col.r > 255) { std::cout << "Tile Update Error" << std::endl; quitGame = true; }
			}
			
		}
		else {
			team = -1;
		}
		
		

	}

	void updateBorders() {
		border_tile = false;
		for (Tile* tile : neighbors) {
			if (tile->team != team) {
				border_tile = true;
				break;
			}
		}
	}

	void draw()
	{
		if (team == -1) {
			return;
		}
		if (pos.x < 0 || pos.x > GAME_MAP_WIDTH || pos.y < 0 || pos.y > GAME_MAP_HEIGHT) {
			return;
		}

		float gx = pos.x - Camera_Pos[0]; float gy = pos.y - Camera_Pos[1];



		circle.setPosition({ gx, gy });
		circle.setOutlineColor(col);
		if (fort_is_assimilating) {
			sf::Color temp_col = opp_col; temp_col.a = col.a * .67;
			circle.setOutlineColor(temp_col);
		}
		circle.setFillColor({ 0,0,0,0 });

		flicker_timer += flicker_timer_vel * 2.5 * GameFPSRatio;
		if (flicker_timer <= 0 || flicker_timer >= 100) {
			flicker_timer_vel = -flicker_timer_vel;
		} // Oscillate border flicker timer
		if (flicker_timer < 0) { flicker_timer = 0; }
		if (flicker_timer > 100) { flicker_timer = 100; }
		float temp = col.a;
		col.a = (col.a / 6) * flicker_timer / 100;
		if (fort_is_assimilating) {
			col.a = col.a / 2;
		}
		circle.setFillColor(col);
		col.a = temp;


		if (border_tile) {
			temp = col.a;
			col.a = col.a / 3;
			circle.setFillColor(col);
			col.a = temp;
		}

		if (flash_timer < 0) { flash_state = false; }
		if (flash_state) {
			flash_timer += flash_vel * GameFPSRatio;
			if (flash_timer > max_flash_time) {
				flash_vel = -flash_vel;
				flash_timer = max_flash_time;
			}

			float ratio = flash_intensity * flash_timer / max_flash_time;


			if (ratio < 0) { ratio = 0; }
			if (ratio > 255) { ratio = 255; }
			flash_col.a = ratio;

			circle.setFillColor(flash_col);
		}

		

		window.draw(circle);

		if (DEBUG_FEATURES && tank_deaths > 0) {
			renderText(window, { gx, gy }, std::to_string(tank_deaths), GameFont, 10, col);
		}
	}
	void flash(float vel, sf::Color t_col, float t_intensity, int type = 0)
	{
		flash_state = true;
		flash_timer = 1;
		max_flash_time = 60;
		flash_vel = vel;
		flash_col = t_col;
		flash_intensity = t_intensity;

		switch (type)
		{
		case 0:
			for (int i = 0; i < 3; i++) {
				SpawnParticle(pos, 4, 1.25, 2, 2, t_col);
			}
			break;
		case 1:
			for (int i = 0; i < 2; i++) {
				SpawnParticle(pos, 3, 1, 2, 1.5, t_col);
			}
			break;
		default:
			break;
		}
		
	}
};



class GameDisplayText
{
public:
	bool ia;
	sf::Vector2f pos;
	float max_life;
	float life;
	bool shadow;
	sf::Text TextObj;
	sf::Color col;
	int size;
	float thickness;


	GameDisplayText(std::string sp_Text, sf::Vector2f sp_pos, sf::Color sp_col, int sp_size, float sp_dur, float sp_thickness, bool sp_shadow = false) :
		ia(true),
		pos(sp_pos),
		size(sp_size),
		max_life(sp_dur * 60),
		life(max_life),
		shadow(sp_shadow),
		thickness(sp_thickness)
	{
		col = sp_col;
		TextObj.setFont(GameFont);
		TextObj.setString(sp_Text);
		TextObj.setCharacterSize(size);
		float x = pos.x - (TextObj.getGlobalBounds().width / 2);
		float y = pos.y - (TextObj.getGlobalBounds().height / 2);

		TextObj.setFillColor(col);
		TextObj.setPosition({ x,y });
		TextObj.setOutlineThickness(thickness);
		

		
	}

	void draw(sf::RenderWindow &surface)
	{
		life--;
		if (life <= 0) { ia = false; return; };

		float a = 192 * 2 * (life / max_life);
		if (a >= 192) { a = 192; }

		col.a = a;

		if (shadow) {
			TextObj.move({ 2,2 });
			sf::Color t_col = dimCol(col, 25);
			t_col.a = col.a;

			TextObj.setFillColor(t_col);
			surface.draw(TextObj);
			TextObj.move({ -2,-2 });

			TextObj.setFillColor(col);
			TextObj.setOutlineColor({ 0,0,0,col.a });
			TextObj.move({ -2,-2 });
			surface.draw(TextObj);
			TextObj.move({ 2,2 });
		}
		else {
			TextObj.setOutlineColor({ 0,0,0,col.a });
			TextObj.setFillColor(col);
			surface.draw(TextObj);
		}

		
		

	}
};



class DeadTank {
public:
	float life;
	sf::Vector2f pos;
	float ang;
	int type;
	bool ia;
	int team;
	sf::Sprite sprite;
	sf::Color col;

	DeadTank()
	{
		life = 0;
		pos = { 0,0 };
		ang = 0;
		type = rand() % 2;
		ia = false;
	}
	void spawn(sf::Vector2f s_pos, float s_ang, int s_team)
	{
		pos = s_pos;
		ang = s_ang;
		team = s_team;
		life = DeadTankLife;
		ia = true;
		sprite.setTexture(DeadTankTextArr[team][type]);
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
		col = oppCol(colorArr[team]);
	}
	void AI()
	{
		life -= GameFPSRatio;
		if (life <= 0) { ia = false; }
	}
	void draw(sf::RenderWindow &surface)
	{
		float ratio = 160.f * (life / DeadTankLife);
		
		sprite.setRotation(ang + 90);
		sprite.setPosition(pos);
		sprite.move({ -Camera_Pos[0], -Camera_Pos[1] });

		sf::Color n_col = sprite.getColor();
		n_col.a = ratio;
		sprite.setColor(n_col);

		surface.draw(sprite);

		ratio = life / DeadTankLife;

		if (rand() % 1000 <= 50 * GameFPSRatio * ratio) { SpawnParticle(pos, 3, 1, 2, 1, col); }
		if (rand() % 1000 <= 25 * GameFPSRatio * ratio) { SpawnParticle(pos, 3, 1, 1, 2, col); }

	}
};



class Button{
public:
	sf::Vector2f pos;
	sf::FloatRect rect;
	sf::Color colour;
	std::string text;
	bool ia;
	int action;
	sf::Text TextObj;
	

	Button(sf::Vector2f sp_pos, sf::Vector2f sp_size, std::string sp_text, sf::Color sp_colour, int sp_action, int sp_textsize) :
		ia(true),
		pos(sp_pos),
		rect(sp_pos.x,sp_pos.y,sp_size.x,sp_size.y),
		text(sp_text),
		colour(sp_colour),
		action(sp_action)
	{
		TextObj.setFont(SecondaryFont);
		TextObj.setString(text);
		TextObj.setCharacterSize(sp_textsize);
		float x = sp_pos.x + (sp_size.x / 2) - (TextObj.getGlobalBounds().width / 2);
		float y = sp_pos.y + (sp_size.y / 2) - (TextObj.getGlobalBounds().height / 2);

		TextObj.setFillColor(colour);
		TextObj.setPosition({ x,y });
	}

	void draw() 
	{
		sf::Color n_colour = colour;
		n_colour.a = 85;
		drawFilledRect(window, rect, n_colour);
		drawRect(window, rect, colour, 2);

		window.draw(TextObj);
	}

	void fire(){
		switch (action)
		{
		case 0:  // Quit Game
			quitGame = true;
			break;
		case 1:  // DemoGame
			DemoGame();
			break;
		case numberOfTeams + 2: // Delete Entities
			GameTextArr.clear();
			EntityArr.clear();
			DeadTankArr.clear();
			SpawnGameText("ENTITIES DELETED", { (float)(SCREEN_WIDTH / 2), (float)(SCREEN_HEIGHT / 2) }, { 255, 255, 255 }, 30, 5, 2, true);
			break;
		case numberOfTeams + 3: // Null Team Summoning
			summonTeam = -1;
			break;


		default:
			if (action > 1 && action < numberOfTeams + 2) {
				summonTeam = action - 2;
			}
			break;
		}
	}

};





class Resource {
public:
	sf::Vector2f pos;
	int amount;
	int type;

	Resource(){}
	void draw(){}
};













int main()
{
	srand(time(0));

	if (devWindow) { SCREEN_WIDTH = SCREEN_WIDTH / 2; SCREEN_HEIGHT = SCREEN_HEIGHT / 2; }
	MiniMapRect = { (float)SCREEN_WIDTH - (float)MINIMAP_WIDTH - 50, (float)SCREEN_HEIGHT - (float)MINIMAP_HEIGHT - 50, (float)MINIMAP_WIDTH, (float)MINIMAP_HEIGHT };
	if (!devWindow) { window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Tank Attack", sf::Style::Fullscreen); }
	else {
		window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Tank Attack");
	}

	// ---------------------------------- G A M E   S E T U P --------------------------------------------------------------------------





	// Load Sound Files and Music
	background_Music.openFromFile("files/audio/SimpleRepeat.ogg");
	background_Music.play();
	background_Music.setLoop(true);


	b_tankshoot01.loadFromFile("files/audio/tankshoot.wav");
	b_tankshoot02.loadFromFile("files/audio/tankshoot2.wav");
	b_fortshoot01.loadFromFile("files/audio/fortshoot.wav");
	b_fortcaptured01.loadFromFile("files/audio/fortcaptured.wav");
	b_laserhit01.loadFromFile("files/audio/laserhit.wav");
	b_tankreload01.loadFromFile("files/audio/tankreload.wav");
	b_tankdies01.loadFromFile("files/audio/tankdies.wav");
	b_tankdies02.loadFromFile("files/audio/tankdies2.wav");
	b_tankcreated01.loadFromFile("files/audio/tankcreated.wav");

	tankshoot01.setVolume(20);
	tankshoot02.setVolume(20);
	fortshoot01.setVolume(20);
	laserhit01.setVolume(33);
	tankdies01.setVolume(20);
	tankdies02.setVolume(20);
	tankreload01.setVolume(15);
	tankcreated01.setVolume(5);
	fortcaptured01.setVolume(45);


	// Load Unit Texures

	TankImg.loadFromFile("files/images/comptank.png");
	FortImg.loadFromFile("files/images/fort.png");
	DeadTankImg[0].loadFromFile("files/images/deadtank01.bmp");
	DeadTankImg[1].loadFromFile("files/images/deadtank02.bmp");

	for (int i = 0; i < numberOfTeams; i++) {
		CompTankImgArr[i] = transformImgCol(TankImg, colorArr[i]);
		CompTankTextArr[i].loadFromImage(CompTankImgArr[i]);

		FortImgArr[i] = transformImgCol(FortImg, colorArr[i]);
		FortTextArr[i].loadFromImage(FortImgArr[i]);

		DeadTankImgArr[i][0] = transformImgCol(DeadTankImg[0], colorArr[i]);
		DeadTankImgArr[i][1] = transformImgCol(DeadTankImg[1], colorArr[i]);
		DeadTankImgArr[i][0].createMaskFromColor({ 0,128,128 });
		DeadTankImgArr[i][1].createMaskFromColor({ 0,128,128 });
		DeadTankTextArr[i][0].loadFromImage(DeadTankImgArr[i][0]);
		DeadTankTextArr[i][1].loadFromImage(DeadTankImgArr[i][1]);



	}


	if (not interlocking_tiles)
		hexagon_tiles = false;


	// Load Fonts
	GameFont.loadFromFile("files/fonts/VerminVibesV-Zlg3.ttf");
	SecondaryFont.loadFromFile("files/fonts/JustMyType-KePl.ttf");






	// ---------------------------------- G A M E   S E T U P   E N D --------------------------------------------------------------------------



	// Game Instance Setup



	StageColour = { 0,0,0 };
	LastFPS = 60;
	window.setFramerateLimit(60);
	InitTiles();

	// -----------  G A M E   L O O P  ----------------------------------------------------------------------------------------
	sf::Clock  clock, FPSClock;
	int frames = 0; int frames2 = 0;
	GameFPSRatio = 1;

	SpawnGameText("GAME STARTED", { (float)(SCREEN_WIDTH / 2), (float)(SCREEN_HEIGHT / 2) }, { 255, 255, 255 }, 30, 10, 2, true);

	loadGameButtons();


	// MAIN GAME LOOP
	while (!quitGame) {

		game_ticks++; frames++; frames2++; current_game_timer++;
		if (game_ticks > 1'000'000'000) { quitGame = true; }

		if (game_ticks % 4 == 0) { updateStats(); }
		extra_population = round(current_game_timer / extra_population_interval) * extra_population_quanta;
		if (game_ticks % 45 == 0) { std::cout << "Current Game Timer: " << current_game_timer << "| Extra Population: " << extra_population << std::endl; }





		handleEvents(window);
		keyboardInputs();

		window.clear();
		if (eventLogging) { std::cout << std::endl; std::cout << "//---- Frame Begins ----//" << std::endl; }
		// Render Game
		GameScreenRect = { Camera_Pos[0] - 25, Camera_Pos[1] - 25, SCREEN_WIDTH + 50, SCREEN_HEIGHT + 50 };
		drawFilledRect(window, { -Camera_Pos[0], -Camera_Pos[1], GAME_MAP_WIDTH, GAME_MAP_HEIGHT }, StageColour);
		if (draw_Tiles) { DrawTiles(); }
		RenderDeadTanks(); if (eventLogging) { std::cout << std::endl; std::cout << "/Dead Tanks Rendered/" << std::endl; }
		RenderEntities();  if (eventLogging) { std::cout << std::endl; std::cout << "/Entities Rendered/" << std::endl; }
		RenderLasers();    if (eventLogging) { std::cout << std::endl; std::cout << "/Lasers Rendered/" << std::endl; }
		RenderMissles();   if (eventLogging) { std::cout << std::endl; std::cout << "/Missles Rendered/" << std::endl; }
		if (!draw_particles) { ParticleArr.clear(); }
		RenderParticles(); if (eventLogging) { std::cout << std::endl; std::cout << "/Particles Rendered/" << std::endl; }
		if (draw_UI) { DrawUI(window);    if (eventLogging) { std::cout << std::endl; std::cout << "/UI Rendered/" << std::endl; } }
		if (draw_minimap && game_ticks) { RenderMinimap(); if (eventLogging) { std::cout << std::endl; std::cout << "/Minimap Rendered/" << std::endl; } }
		updateWind();
		if (draw_Tiles && game_ticks % 45 == 0) { UpdateTiles(); }



		// Update Population Data
		if (game_ticks % 180 == 0) {
			std::array<int, numberOfTeams> pops;
			std::array<float, numberOfTeams> f_pops;


			for (int i = 0; i < numberOfTeams; i++) {	// Update Tank Population
				pops[i] = getTankPop(i);
			}
			TankPopArr.push_back(pops);



			for (int i = 0; i < numberOfTeams; i++) {	// Update Fort Population
				pops[i] = getFortPop(i);
			}
			FortPopArr.push_back(pops);



			for (int i = 0; i < numberOfTeams; i++) {	// Update Captured Fort Population
				pops[i] = getFortPop(i, true);
			}
			CapturedFortPopArr.push_back(pops);



			for (int i = 0; i < numberOfTeams; i++) {	// Update Captured Fort Ratio
				if (getFortPop(i) != 0) {// prevent divide by zero error
					f_pops[i] = (float)getFortPop(i, true) / (float)getFortPop(i);
				}
				else {
					f_pops[i] = 0;
				}
			}
			CapturedFortRatioArr.push_back(f_pops);



			for (int i = 0; i < numberOfTeams; i++) {	// Update Special Tank Population
				pops[i] = getSpecialTankPop(i);
			}
			SpecialTankPopArr.push_back(pops);



			for (int i = 0; i < numberOfTeams; i++) {	// Update Special Tank Ratio
				f_pops[i] = (float)getSpecialTankPop(i) / (float)getTankPop(i);
			}
			SpecialTankRatioArr.push_back(f_pops);



			for (int i = 0; i < numberOfTeams; i++) {	// Update Special Fort Population
				pops[i] = getSpecialFortPop(i);
			}
			SpecialFortPopArr.push_back(pops);



			for (int i = 0; i < numberOfTeams; i++) {	// Update Special Fort Ratio
				f_pops[i] = (float)getSpecialFortPop(i) / (float)getFortPop(i);
			}
			SpecialFortRatioArr.push_back(f_pops);



			for (int i = 0; i < numberOfTeams; i++) {	// Update Killed Tanks
				pops[i] = PvP_Tanks_Killed[i];
			}
			TanksKilledArr.push_back(pops);



			for (int i = 0; i < numberOfTeams; i++) {		// Update Lost Tanks
				pops[i] = PvP_Tanks_Lost[i];
			}
			TanksLostArr.push_back(pops);



			for (int i = 0; i < numberOfTeams; i++) {	// Update Average Tank Age
				pops[i] = getAverageTankAge(i);
			}
			AverageTankAgeArr.push_back(pops);



			for (int i = 0; i < numberOfTeams; i++) {	// Update Tile number
				pops[i] = getTerritory(i);
			}
			TeamTerritoryArr.push_back(pops);
		}


		// Demo Game Autoplay
		if (game_ticks % (60 * 30) == 0 && false) {
			int teams_remaining = 0;
			for (int i = 0; i < numberOfTeams; i++) {
				if (getFortPop(i) > 0) {
					teams_remaining += 1;
					if (teams_remaining > 1) { break; }
				}
			}
			if (teams_remaining == 1) { DemoGame(rand() % 2); }
		}

		// End Render Game
		if (eventLogging) { std::cout << std::endl; std::cout << "//---- Frame Ends ----//" << std::endl; }
		window.display();

		// Calcilate FPS
		if (clock.getElapsedTime().asSeconds() >= 1) {
			updateStageColour();
			LastFPS = frames; // Update FPS
			frames = 0; clock.restart();
		}
		// Set Game Frame Ratio for smooth Gameplay
		if (FPSClock.getElapsedTime().asMicroseconds() >= 1'000'000 / 2) {
			GameFPSRatio = (60.f / frames2) * 0.5;		// multiplier to prevent jarring game pace
			if (GameFPSRatio > 6) { GameFPSRatio = 6; } // Prevent Insane movement in case of Lag Spikes
			frames2 = 0; FPSClock.restart();
		}





		// -----------  G A M E   L O O P   E N D  ----------------------------------------------------------------------------------------




		
	}
	window.close();



	return 0;
}














sf::Image transformImgCol(sf::Image img, sf::Color tcol) {
	sf::Image newImg;
	newImg.create(img.getSize().x, img.getSize().y, sf::Color::Transparent);
	newImg.createMaskFromColor(sf::Color(0, 128, 128));

	for (unsigned int x = 0; x < img.getSize().x; x++) {
		for (unsigned int y = 0; y < img.getSize().y; y++) {
			sf::Color col = img.getPixel(x, y);

			if (col.r == col.g && col.g == col.b && col.r != 0 && col.r != 254) {
				sf::Color pixcol;
				if (col.r > 127.5) {
					pixcol.r = ((col.r - 127.5) / 127.5) * tcol.r;
					pixcol.g = ((col.r - 127.5) / 127.5) * tcol.g;
					pixcol.b = ((col.r - 127.5) / 127.5) * tcol.b;
				}
				else {
					pixcol.r = (-(col.r - 127.5) / 127.5) * (255 - tcol.r);
					pixcol.g = (-(col.r - 127.5) / 127.5) * (255 - tcol.g);
					pixcol.b = (-(col.r - 127.5) / 127.5) * (255 - tcol.b);
				}
				newImg.setPixel(x, y, pixcol);
			}
			else {
				newImg.setPixel(x, y, col);
			}
		}
	}
	return newImg;
}

void renderText(sf::RenderWindow& surface, const sf::Vector2f& pos, const std::string& Text, const sf::Font& font, int size, const sf::Color& fill_col, int outline_thickness, const sf::Color& outline_col, bool centered)
{
	static sf::Text TextSprite;
	static std::string cachedText;
	static sf::FloatRect cachedBounds;

	if (Text != cachedText || &font != TextSprite.getFont() || size != TextSprite.getCharacterSize())
	{
		TextSprite.setFont(font);
		TextSprite.setCharacterSize(size);
		cachedBounds = TextSprite.getLocalBounds();
		cachedText = Text;
	}

	TextSprite.setString(Text);
	TextSprite.setFillColor(fill_col);
	TextSprite.setOutlineColor(outline_col);
	TextSprite.setOutlineThickness(outline_thickness);

	if (centered) {
		float x = TextSprite.getLocalBounds().width / 2;
		float y = TextSprite.getLocalBounds().height / 2;

		TextSprite.setOrigin({ x,y });
	}
	else {
		TextSprite.setOrigin({ 0,0 });
	}
	
	TextSprite.setPosition(pos);

	surface.draw(TextSprite);
}

bool compareTeam(const std::vector <int> &team1, const std::vector <int> team2)
{
	return team1[1] > team2[1];
}

sf::Color dimCol(sf::Color col, float perc)
{
	float p = perc / 100;
	return sf::Color{ (sf::Uint8)(col.r * p), (sf::Uint8)(col.g * p), (sf::Uint8)(col.b * p), 255 };
}

sf::Color oppCol(const sf::Color &col)
{
	return { (sf::Uint8)(255 - col.r), (sf::Uint8)(255 - col.g), (sf::Uint8)(255 - col.b), 255 };
}

sf::Color stage_Colour()
{
	std::vector <int> Teams_Active;
	std::vector <sf::Color> col;
	for (int i = 0; i < numberOfTeams; i++) {
		if (getTankPop(i) > 0 || getFortPop(i) > 0) {
			Teams_Active.push_back(i);
			col.push_back(colorArr[i]);
		}
	}

	sf::Color stgCol;
	float r, g, b;
	r = 0; g = 0; b = 0;

	if (Teams_Active.size() > 0) {
		for (int i = 0; i < Teams_Active.size(); i++) {
			r += col[i].r;
			g += col[i].g;
			b += col[i].b;
		}
		r = (r / Teams_Active.size()) / 8;
		g = (g / Teams_Active.size()) / 8;
		b = (b / Teams_Active.size()) / 8;
	}
	else {
		return {8, 8, 8, 255};
	}

	stgCol = { (sf::Uint8)r, (sf::Uint8)g, (sf::Uint8)b };
	return stgCol;
}

void handleEvents(sf::RenderWindow& myWindow)
{
	static bool MiniMapHighlight;

	if (MiniMapHighlight) {
		float dx = Mouse_Pos.x - MiniMapRect.left;
		float dy = Mouse_Pos.y - MiniMapRect.top;

		dx *= (GAME_MAP_WIDTH / MINIMAP_WIDTH);
		dy *= (GAME_MAP_HEIGHT / MINIMAP_HEIGHT);

		Camera_Pos[0] = dx - SCREEN_WIDTH / 2;
		Camera_Pos[1] = dy - SCREEN_HEIGHT / 2;
	}
	if (eventLogging) { std::cout << "/HANDLEEVENTS()/" << std::endl; }

	// Check Mouse Position for Mouse Scrolling
	if (!Camera_Follow_Tank) {
		float screen_scroll_width = 10;
		if (Mouse_Pos.x <= screen_scroll_width) { Camera_Pos[0] -= GameFPSRatio * SCROLL_SENSITIVITY; }
		if (Mouse_Pos.x >= SCREEN_WIDTH - screen_scroll_width) { Camera_Pos[0] += GameFPSRatio * SCROLL_SENSITIVITY; }

		if (Mouse_Pos.y <= screen_scroll_width) { Camera_Pos[1] -= GameFPSRatio * SCROLL_SENSITIVITY; }
		if (Mouse_Pos.y >= SCREEN_HEIGHT - screen_scroll_width) { Camera_Pos[1] += GameFPSRatio * SCROLL_SENSITIVITY; }
	}
	


	// Camera follows Tank
	if (Camera_Follow_Tank) {
		
		if (Tank_Followed != nullptr) {
			bool is_valid = false;
			for (auto& entity : EntityArr) {
				if (&entity == Tank_Followed) {
					is_valid = true;
					break;
				}
			}
			if (!is_valid) {
				Tank_Followed = nullptr;
			}
		}
		// If Tank being followed is NULL or shuffled
		if (Tank_Followed == nullptr || Tank_Followed_uniqueID != Tank_Followed->uniqueID) {
			bool found = false;
			// Find Tank with matching ID
			for (int i = 0; i < EntityArr.size(); i++) {
				if (EntityArr[i].ia && EntityArr[i].uniqueID == Tank_Followed_uniqueID && EntityArr[i].ID == "tank") {
					Tank_Followed = &EntityArr[i];
					found = true;
					break;
				}
			}
			// If Tank not found, stop Camera Follow
			if (!found) {
				std::vector <Entity*> temp_TankArray;
				
				Camera_Follow_Tank = false;
				for (int i = 0; i < EntityArr.size(); i++) {
					if (EntityArr[i].ID == "tank") {
						temp_TankArray.push_back(&EntityArr[i]);
					}
				}

				if (temp_TankArray.size() > 0) {
					Camera_Follow_Tank = true;
					Tank_Followed = temp_TankArray[rand() % temp_TankArray.size()];
					Tank_Followed_uniqueID = Tank_Followed->uniqueID;
				}
				
			}
		}
		else {
			// Camera Follows Tank
			Camera_Pos[0] = Tank_Followed->pos[0] - SCREEN_WIDTH / 2;
			Camera_Pos[1] = Tank_Followed->pos[1] - SCREEN_HEIGHT / 2;

			
		}

	}

	float x, y;

	sf::Event event;
	while (myWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			quitGame = true;
			break;

		case sf::Event::MouseButtonReleased:
			MiniMapHighlight = false;
			break;


		case sf::Event::MouseButtonPressed:

			// Check for Left Click
			if (event.mouseButton.button == sf::Mouse::Left) {
				if (eventLogging) { std::cout << "  *Left Click*" << std::endl; }
				x = event.mouseButton.x;
				y = event.mouseButton.y;
				Mouse_Pos = { x, y };

				// Check for Buttons First
				bool buttonClicked = false;
				for (int i = 0; i < ButtonArr.size(); i++) {
					if (ButtonArr[i].ia) {
						if (ButtonArr[i].rect.contains(Mouse_Pos)) {
							ButtonArr[i].fire();
							buttonClicked = true;
						}
					}
				}
				if (buttonClicked) { break; }

				// Check for Minimap
				bool miniMapClicked = false;

				
				if (MiniMapRect.contains(Mouse_Pos) && draw_minimap) {
					float dx = Mouse_Pos.x - MiniMapRect.left;
					float dy = Mouse_Pos.y - MiniMapRect.top;

					dx *= (GAME_MAP_WIDTH / MINIMAP_WIDTH);
					dy *= (GAME_MAP_HEIGHT / MINIMAP_HEIGHT);

					Camera_Pos[0] = dx - SCREEN_WIDTH / 2;
					Camera_Pos[1] = dy - SCREEN_HEIGHT / 2;
					miniMapClicked = true;
					MiniMapHighlight = true;
				}
				if (miniMapClicked) { break; }

				// Check for Clicking Forts
				bool fortClicked = false;
				for (int i = 0; i < EntityArr.size(); i++) {  // Run through all Entities
					if (EntityArr[i].ID == "fort") {  // Filter Out Tanks
						if (EntityArr[i].collisionRect().contains({Mouse_Pos.x + Camera_Pos[0], Mouse_Pos.y + Camera_Pos[1]})) {  // Check for Click
							fortClicked = true;
							for (int j = 0; j < TileArr.size(); j++) {
								if (TileArr[j].FortID == EntityArr[i].uniqueID) {
									TileArr[j].flash(5, EntityArr[i].col, 64, 1);
								}
							}
						}
					}
				}
				if (fortClicked) { break; }

				if (summonTeam == -1) { break; } // Check if NULL team select

				// Spawn Tanks
				sf::FloatRect temp_rect{ -Camera_Pos[0],-Camera_Pos[1], GAME_MAP_WIDTH, GAME_MAP_HEIGHT };
				if (temp_rect.contains({ x,y })) {
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){ SpawnTank({ x + Camera_Pos[0], y + Camera_Pos[1] }, summonTeam, 1); }
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) { SpawnTank({ x + Camera_Pos[0], y + Camera_Pos[1] }, summonTeam, 0, true); }
					else { SpawnTank({ x + Camera_Pos[0], y + Camera_Pos[1] }, summonTeam); }
				}
			}
			// Check for Right Click
			else if (event.mouseButton.button == sf::Mouse::Right) {
				if (eventLogging) { std::cout << "  *Right Click*" << std::endl; }
				x = event.mouseButton.x;
				y = event.mouseButton.y;
				Mouse_Pos = { x, y };

				if (summonTeam == -1) { break; }

				// Spawn Forts
				sf::FloatRect temp_rect{ -Camera_Pos[0],-Camera_Pos[1], GAME_MAP_WIDTH, GAME_MAP_HEIGHT };
				if (temp_rect.contains({ x,y })) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) { SpawnFort({ x + Camera_Pos[0], y + Camera_Pos[1] }, summonTeam, NULL, true); }
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) { SpawnFort({ x + Camera_Pos[0], y + Camera_Pos[1] }, summonTeam, true); }
					else { SpawnFort({ x + Camera_Pos[0], y + Camera_Pos[1] }, summonTeam); }
				}
			}


			break;

		case sf::Event::KeyPressed:

			switch (event.key.code) {

				// Player presses Escape --> Exit Game
			case sf::Keyboard::Escape:
				if (event.key.code == sf::Keyboard::Escape) {
					if (eventLogging) { std::cout << "  *ESC key pressed*" << std::endl; }
					// quitGame = true;
				}
				break;
			case sf::Keyboard::Delete:
				GameTextArr.clear();
				EntityArr.clear();
				DeadTankArr.clear();
				SpawnGameText("ENTITIES DELETED", { (float)(SCREEN_WIDTH / 2), (float)(SCREEN_HEIGHT / 2) }, { 255, 255, 255 }, 30, 5, 2, true);
				break;
			case sf::Keyboard::Space:
				// Empty Event
				break;


			case sf::Keyboard::R: // Follow Random Tank
				Camera_Follow_Tank = !Camera_Follow_Tank;
				Tank_Followed_uniqueID = NULL;
				break;
			case sf::Keyboard::O:  // Toggle Particles
				draw_particles = !draw_particles;
				break;
			case sf::Keyboard::T:  // Toggle Tiles
				draw_Tiles = !draw_Tiles;
				break;
			case sf::Keyboard::D:  // Toggle F3 screen
				DEBUG_FEATURES = !DEBUG_FEATURES;
				break;
			case sf::Keyboard::A:  // Screenshot
				ScreenShot(window);
				break;
			case sf::Keyboard::U:  // Toggle UI
				draw_UI = !draw_UI;
				break;
			case sf::Keyboard::M:  // Toggle Minimap
				draw_minimap = !draw_minimap;
				break;
			case sf::Keyboard::P: // Pause
				paused = !paused;
				break;
			case sf::Keyboard::W: // Wind Physics
				WIND_Physics = !WIND_Physics;
				break;
			case sf::Keyboard::J: // Record JSON data
				//recording = !recording;
				
				saveJSONData();

				break;
			case sf::Keyboard::S:
				saveGameState("SaveGame.json");
				break;
			}
		

		


			break;

		case sf::Event::MouseMoved:
			x = event.mouseMove.x;
			y = event.mouseMove.y;
			Mouse_Pos = { x, y };
			break;
		

		}

		
	}

	if (eventLogging) { std::cout << "  HANDLEEVENTS() executed." << std::endl; }
}

void keyboardInputs()
{
	if (eventLogging) { std::cout << "/KEYBOARDINPUTS()/" << std::endl; }

	// Arrow Key Scrolling
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))		{ Camera_Pos[0] -= GameFPSRatio * SCROLL_SENSITIVITY; Camera_Follow_Tank = false; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	{ Camera_Pos[0] += GameFPSRatio * SCROLL_SENSITIVITY; Camera_Follow_Tank = false; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))		{ Camera_Pos[1] -= GameFPSRatio * SCROLL_SENSITIVITY; Camera_Follow_Tank = false; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))		{ Camera_Pos[1] += GameFPSRatio * SCROLL_SENSITIVITY; Camera_Follow_Tank = false; }

	
	// Changing Team of Summoned Units
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) { summonTeam = 0; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) { summonTeam = 1; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) { summonTeam = 2; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) { summonTeam = 3; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) { summonTeam = 4; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) { summonTeam = 5; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) { summonTeam = 6; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) { summonTeam = 7; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) { summonTeam = 8; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) { summonTeam = 9; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) { summonTeam = 10; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) { summonTeam = 11; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) { summonTeam = 12; }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) { summonTeam = 13; }
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
		if (game_volume > 0) {
			game_volume -= 1;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
		if (game_volume < 100) {
			game_volume += 1;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) || sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
		tankshoot01.setVolume(20 * game_volume / 100);
		tankshoot02.setVolume(20 * game_volume / 100);
		fortshoot01.setVolume(20 * game_volume / 100);
		laserhit01.setVolume(33 * game_volume / 100);
		tankdies01.setVolume(20 * game_volume / 100);
		tankdies02.setVolume(20 * game_volume / 100);
		tankreload01.setVolume(15 * game_volume / 100);
		tankcreated01.setVolume(5 * game_volume / 100);
		fortcaptured01.setVolume(250 * game_volume / 100);

		background_Music.setVolume(game_volume);
	}
	

	// Make Sure Camera Stays Within Bounds
	if (Camera_Pos[0] <= -SCREEN_WIDTH / 3) {Camera_Pos[0] = -SCREEN_WIDTH / 3;}
	if (Camera_Pos[0] >= GAME_MAP_WIDTH - 2 * SCREEN_WIDTH / 3) { Camera_Pos[0] = GAME_MAP_WIDTH - 2 * SCREEN_WIDTH / 3; }

	if (Camera_Pos[1] <= -SCREEN_HEIGHT / 3) { Camera_Pos[1] = -SCREEN_HEIGHT / 3; }
	if (Camera_Pos[1] >= GAME_MAP_HEIGHT - 2 * SCREEN_HEIGHT / 3) { Camera_Pos[1] = GAME_MAP_HEIGHT - 2 * SCREEN_HEIGHT / 3; }

	if (eventLogging) { std::cout << "  KEYBOARDINPUTS() executed" << std::endl; }
}

void drawBorders()
{
	if (Camera_Pos[0] <= 0)
	{
		sf::FloatRect temp_rect;
		temp_rect = { 0, 0, - Camera_Pos[0], SCREEN_HEIGHT };
		drawFilledRect(window, temp_rect, {0,0,0});
	}
}

bool File_Exists(const std::string &fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}

bool Folder_Exists(const std::string& folderName)
{
	struct stat info;
	if (stat(folderName.c_str(), &info) != 0) {
		return false;
	}
	return (info.st_mode & S_IFDIR) != 0;
}

void ScreenShot(sf::RenderWindow& surface)
{
	int var; // To remove annoying warnings on Visual Studio
	if (!Folder_Exists("screenshots")) {
		var = _mkdir("screenshots");
	}
	var = _chdir("screenshots");
	
	
	sf::Vector2u size = surface.getSize();
	sf::Texture texture;
	texture.create(size.x, size.y);
	texture.update(surface);
	sf::Image screenshot = texture.copyToImage();

	
	
	std::time_t now = std::time(nullptr);
	std::tm local;
	localtime_s(&local, &now);
	std::stringstream ss;
	ss << std::put_time(&local, "%Y-%m-%d %H-%M-%S");
	std::string datetime = ss.str();

	screenshot.saveToFile("Screenshot " + datetime + ".png");

	var = _chdir("../");
}

void RenderEntities()
{
	if (eventLogging) { std::cout << "/RENDERENTITIES()/" << std::endl; }


	// Draw Tanks first, then forts
	for (auto& entity: EntityArr) {
		if (entity.ID == "tank" && entity.ia) {
			if (!paused) { entity.AI(); }
			if (GameScreenRect.contains({entity.pos[0], entity.pos[1] })) {entity.draw();}
		}
	}
	int size = EntityArr.size();
	for (int i = 0; i < size; i++) {
		if (EntityArr[i].ID == "fort" && EntityArr[i].ia) {
			if (!paused) { EntityArr[i].AI(); }
			if (GameScreenRect.contains({ EntityArr[i].pos[0], EntityArr[i].pos[1]})) { EntityArr[i].draw(); }
		}
	}

	
	for (int i = 0; i < size; i++) {
		if (!EntityArr[i].ia) {
			TankDeathPositions.push_back({ EntityArr[i].pos[0], EntityArr[i].pos[1]});
		}
	}
	

	EntityArr.erase(
		std::remove_if(EntityArr.begin(), EntityArr.end(),
			[](const Entity& e) { return !e.ia; }),
		EntityArr.end()
	);

	//shuffle EntityArr


	if (game_ticks % 1200 == 0) {
		if (eventLogging || true) {
			std::cout << std::endl;
			std::cout << "###== [Gametick:" << std::to_string(game_ticks) << "]  Entities Shuffled ==###" << std::endl;
			std::cout << std::endl;
		}
		int size = EntityArr.size();
		std::vector<Entity> tmp_Arr;
		for (int i = 0; i < EntityArr.size(); i++) {
			EntityArr[i].ammo_Target = nullptr;
			EntityArr[i].enemy = nullptr;

			tmp_Arr.push_back(EntityArr[i]);
		}


	
		EntityArr.clear();
		int temp = rand();
		for (int i = 0; i < size; i++) {
			double index = tmp_Arr.size() * static_cast<double>(rand() % 100) / 100;
			EntityArr.push_back(tmp_Arr[(int)index]);
			tmp_Arr.erase(tmp_Arr.begin() + (int)index);
		}

		
	}

	if (eventLogging) { std::cout << "  RENDERENTITIES() executed" << std::endl; }

}

void RenderLasers() {
	if (eventLogging) { std::cout << "/RENDERLASERS()/" << std::endl; }

	int size = LaserArr.size();
	for (auto& laser : LaserArr) {
		if (!paused) { laser.move(); }
		if(GameScreenRect.contains(laser.pos)) { laser.draw(); }
	}

	// remove inactive lasers
	LaserArr.erase(
		std::remove_if(LaserArr.begin(), LaserArr.end(),
			[](const Laser& l) { return !l.ia; }),
		LaserArr.end()
	);

	if (eventLogging) { std::cout << "  RENDERLASERS() executed" << std::endl; }
}

void RenderParticles()
{
	if (eventLogging) { std::cout << "RENDERPARTICLES() called..." << std::endl; }


	for (auto& particle : ParticleArr) {
		if (!paused) { particle.move(); }
		particle.draw();
		//if (!GameScreenRect.contains(ParticleArr[i].pos)) { ParticleArr[i].ia = false; }
	}

	// cull inactive Particles
	ParticleArr.erase(
		std::remove_if(ParticleArr.begin(), ParticleArr.end(),
			[](const Particle& p) { return !p.ia; }),
		ParticleArr.end()
	);

	if (eventLogging) { std::cout << "RENDERPARTICLES() executed." << std::endl; }
}

void RenderMissles()
{
	if (eventLogging) { std::cout << "/RENDERMISSLES()/" << std::endl; }


	for (int i = 0; i < MissleArr.size(); i++) {
		if (!paused) { MissleArr[i].move(); }
		if (GameScreenRect.contains(MissleArr[i].pos)) { MissleArr[i].draw(); }
	}

	// remove inactive lasers
	for (int i = 0; i < MissleArr.size(); i++) {
		if (!MissleArr[i].ia) {
			MissleArr.erase(MissleArr.begin() + i);
		}
	}

	if (eventLogging) { std::cout << "  RENDERMISSLES() executed" << std::endl; }
}

void RenderMinimap()
{
	if (eventLogging) { std::cout << "/RENDERMINIMAP()/" << std::endl; }

	

	sf::Color t_col = StageColour;
	t_col.a = 192;
	sf::Vector2f t_pos, g_pos, g_size;

	const float inv_GAME_MAP_WIDTH = 1.0f / GAME_MAP_WIDTH;
	const float inv_GAME_MAP_HEIGHT = 1.0f / GAME_MAP_HEIGHT;
	const float width_scale = MINIMAP_WIDTH * inv_GAME_MAP_WIDTH;
	const float height_scale = MINIMAP_HEIGHT * inv_GAME_MAP_HEIGHT;


	drawFilledRect(window, MiniMapRect, t_col);
	drawRect(window, MiniMapRect, oppCol(StageColour), 1);

	// Draw Tiles
	if (draw_Tiles) {
		g_size.x = Tiles_Size * width_scale;
		g_size.y = Tiles_Size * height_scale;

		sf::VertexArray tileQuads(sf::Quads);
		for (const auto& tile : TileArr) {
			if (tile.team != -1) {
				t_pos = tile.pos;
				g_pos.x = t_pos.x * width_scale + MiniMapRect.left;
				g_pos.y = t_pos.y * height_scale + MiniMapRect.top;

				sf::Color c = tile.col;
				float x = g_pos.x, y = g_pos.y, w = g_size.x, h = g_size.y - 1;
				if (tile.border_tile)	{ c.a = tile.col.a * 2; }
				else { 
					c.a = (tile.col.a / 2) + (tile.col.a / 3) * tile.flicker_timer / 50;
					//c.a = tile.col.a;
				}
				tileQuads.append(sf::Vertex({ x,     y }, c));
				tileQuads.append(sf::Vertex({ x + w, y }, c));
				tileQuads.append(sf::Vertex({ x + w, y + h }, c));
				tileQuads.append(sf::Vertex({ x,     y + h }, c));
			}
		}
		window.draw(tileQuads);
	}
	
	// Draw Tanks
	for (Entity& entity : EntityArr) { 
		if (entity.ia && entity.ID == "tank") {
			t_pos = { entity.pos[0], entity.pos[1] };
			g_pos.x = (t_pos.x / GAME_MAP_WIDTH) * MINIMAP_WIDTH + MiniMapRect.left;
			g_pos.y = (t_pos.y / GAME_MAP_HEIGHT) * MINIMAP_HEIGHT + MiniMapRect.top;

			sf::Color col = entity.col;
			if (game_ticks % 180 < 10 && entity.level > 0) { col = oppCol(col); }
			drawFilledRect(window, { g_pos.x - 1, g_pos.y - 1, 2, 2 }, col);
		}
	}
	// Draw Forts
	for (Entity& entity : EntityArr) {
		if (entity.ia && entity.ID == "fort") {
			t_pos = { entity.pos[0], entity.pos[1] };
			g_pos.x = (t_pos.x / GAME_MAP_WIDTH) * MINIMAP_WIDTH + MiniMapRect.left;
			g_pos.y = (t_pos.y / GAME_MAP_HEIGHT) * MINIMAP_HEIGHT + MiniMapRect.top;


			sf::Color col = entity.col;
			if (entity.Tank_spawn_timer < 0) { col = dimCol(col, 60); }
			
			if (entity.special) {
				drawFilledRect(window, { g_pos.x - 3, g_pos.y - 3, 6, 6 }, col);
				drawRect(window, { g_pos.x - 3, g_pos.y - 3, 5, 5 }, dimCol(col, 25), 1);
				//drawRect(window, { g_pos.x - 4, g_pos.y - 4, 7, 7 }, { 0,0,0 }, 1);
			}
			else {
				drawFilledRect(window, { g_pos.x - 2, g_pos.y - 2, 4, 4 }, col);
				drawRect(window, { g_pos.x - 2, g_pos.y - 2, 4, 4 }, dimCol(entity.col, 25), 1);
				//drawRect(window, { g_pos.x - 3, g_pos.y - 3, 6, 6 }, { 0,0,0 }, 1);
			}
		}
	}

	g_pos.x = (Camera_Pos[0] * MINIMAP_WIDTH / GAME_MAP_WIDTH) + MiniMapRect.left;
	g_pos.y = (Camera_Pos[1] * MINIMAP_HEIGHT / GAME_MAP_HEIGHT) + MiniMapRect.top;

	t_pos.x = SCREEN_WIDTH * MINIMAP_WIDTH / GAME_MAP_WIDTH;
	t_pos.y = SCREEN_HEIGHT * MINIMAP_HEIGHT / GAME_MAP_HEIGHT;

	drawRect(window, {g_pos.x, g_pos.y, t_pos.x, t_pos.y}, oppCol(StageColour), 1);


	if (eventLogging) { std::cout << "  RENDERMINIMAP() executed" << std::endl; }
}

void RenderGameTexts(sf::RenderWindow &surface)
{
	for (int i = 0; i < GameTextArr.size(); i++) {
		GameTextArr[i].draw(surface);
	}

	for (int i = 0; i < GameTextArr.size(); i++) {
		if (!GameTextArr[i].ia) {
			GameTextArr.erase(GameTextArr.begin() + i);
		}
	}
}

void RenderDeadTanks()
{
	for (int i = 0; i < DeadTankArr.size(); i++) {
		if (!paused) { DeadTankArr[i].AI(); }
		if (GameScreenRect.contains(DeadTankArr[i].pos)) { DeadTankArr[i].draw(window); }
	}

	for (int i = 0; i < DeadTankArr.size(); i++) {
		if (!DeadTankArr[i].ia) {
			DeadTankArr.erase(DeadTankArr.begin() + i);
		}
	}
}

void RenderButtons() {
	for (int i = 0; i < ButtonArr.size(); i++) {
		ButtonArr[i].draw();
	}

	for (int i = 0; i < ButtonArr.size(); i++) {
		if (!ButtonArr[i].ia) {
			ButtonArr.erase(ButtonArr.begin() + i);
		}
	}
}

void DrawUI(sf::RenderWindow &surface)
{
	// Draw FPS
	
	renderText(surface, { 5 + SCREEN_WIDTH - 70, 30 + 5 }, std::to_string((int)LastFPS), GameFont, 40, { 32,32,32,192 }, 2, { 0,0,0,192 });
	renderText(surface, { SCREEN_WIDTH - 70, 30 }, std::to_string((int)LastFPS), GameFont, 40, { 255,255,255,192 }, 2, { 0,0,0,192 });


	//Render Game Stats
	if (DEBUG_FEATURES) {
		std::string text = "Entities Loaded: " + std::to_string(EntityArr.size());
		renderText(surface, { SCREEN_WIDTH - 75, 125 }, text, SecondaryFont, 20, { 255,255,255,192 }, 1, { 0,0,0,192 });
		text = "Particles Loaded: " + std::to_string(ParticleArr.size());
		renderText(surface, { SCREEN_WIDTH - 75, 150 }, text, SecondaryFont, 20, { 255,255,255,192 }, 1, { 0,0,0,192 });
	}

	// Show Team Stats

	// Show Team Forts
	int j, k;
	std::vector <std::vector<int>> teamList;
	sf::Color n_col;

	for (int i = 0; i < numberOfTeams; i++) {
		if (getFortPop(i) > 0) {
			teamList.push_back({ i, getFortPop(i) });
		}
	}
	// sort team list
	sort(teamList.begin(), teamList.end(), compareTeam);
	// Display Team Fort Stats
	for (int i = 0; i < teamList.size(); i++) {
		j = teamList[i][0]; k = teamList[i][1];
		n_col = colorArr[j]; n_col.a = 128;
		std::string text;

		if (!DEBUG_FEATURES) {
			text = "Forts: " + std::to_string(k) + "[" + std::to_string(getSpecialFortPop(j)) + "]   (" + std::to_string(int(TeamTilePerc[j])) + "%)";
		}
		else {
			text = "Forts: " + std::to_string(k) + "  C/L: " + std::to_string(Forts_Destroyed[j]) + "/" + std::to_string(Forts_Lost[j]);
		}
		

		renderText(surface, { 5, 25.f + (25 * i) }, text, SecondaryFont, 20, n_col, 1, { 0,0,0,n_col.a }, false);
	}


	// Show Team Tanks
	float last_y = 25 + (teamList.size() * 25);
	teamList.clear();

	for (int i = 0; i < numberOfTeams; i++) {
		if (getTankPop(i) > 0) {
			teamList.push_back({ i, getTankPop(i) });
		}
	}
	// sort team list
	sort(teamList.begin(), teamList.end(), compareTeam);
	// Display Team Tank Stats
	for (int i = 0; i < teamList.size(); i++) {
		j = teamList[i][0]; k = teamList[i][1];
		n_col = colorArr[j]; n_col.a = 128;
		if (DEBUG_FEATURES) {
			renderText(surface, { 5, 75.f + (25 * i) + last_y }, "Tanks: " + std::to_string(k) + "   K/D: " + std::to_string(Tanks_Killed[j]) + "/" + std::to_string(Tanks_Lost[j]),
				SecondaryFont, 20, n_col, 1, { 0,0,0,n_col.a }, false);
		}
		else {
			renderText(surface, { 5, 75.f + (25 * i) + last_y }, "Tanks: " + std::to_string(k) + "[" + std::to_string(getSpecialTankPop(j)) + "]",
				SecondaryFont, 20, n_col, 1, { 0,0,0,n_col.a }, false);
		}
		
	}
	

	// Render Game texts
	RenderGameTexts(surface);

	

	// DrawButtons
	RenderButtons();
}





void SpawnTank(sf::Vector2f pos, int team, int level, bool no_ammo) {
	if (eventLogging) { std::cout << std::endl; std::cout << "/SPAWNTANK()/" << std::endl; }

	Entity newTank("tank");
	newTank.spawn(pos, team);
	newTank.level = level;
	

	if (no_ammo) {
		newTank.no_ammo = true;
		newTank.ammo_supply = 0;
		newTank.hp = 1;
	}

	EntityArr.push_back(newTank);

	if (eventLogging) { std::cout << "  SPAWNTANK() executed" << std::endl; }
}

void SpawnFort(sf::Vector2f pos, int team, bool captured, bool special) {
	if (eventLogging) { std::cout << std::endl; std::cout << "/SPAWNFORT()/" << std::endl; }

	Entity newFort("fort");
	newFort.spawn(pos, team);
	if (!captured) { newFort.Tank_spawn_timer = 0; }
	else { newFort.Tank_spawn_timer = -fort_assimilation_ticks; }

	if (special) {
		newFort.fort_tanks_healed = newFort.fort_tanks_healed_threshold; 
		newFort.fort_tanks_spawned = newFort.fort_tanks_spawned_threshold;
		newFort.special = true;
	}
	EntityArr.push_back(newFort);

	if (eventLogging) { std::cout << std::endl; std::cout << "  SPAWNFORT() executed" << std::endl; }
}

void SpawnParticle(sf::Vector2f pos, float size, float range, int type, float durRate, sf::Color col)
{
	if (!GameScreenRect.contains(pos) or paused) { return; }
	if (eventLogging && false) { std::cout << std::endl; std::cout << "/SPAWNPARTICLE()/" << std::endl; }

	Particle newPart;
	newPart.spawn(pos, size, range, type, durRate, col);
	ParticleArr.push_back(newPart);

	if (eventLogging && false) { std::cout << std::endl; std::cout << "  SPAWNPARTICLE() executed" << std::endl; }
}

void SpawnLaser(float posx, float posy, float vel, float ang, float dam, float team, Entity* sender, std::vector <float> size) {
	sender = checkEntity(sender);
	if (sender == nullptr) { return; } // Check if sender is valid

	if (eventLogging) { std::cout << "/SPAWNLASER()/" << std::endl; }

	Laser newLaser;
	sf::Vector2f pos = { posx, posy };
	if (newLaser.spawn(pos, vel, ang, dam, team, sender, size)) { LaserArr.push_back(newLaser); }
	

	if (eventLogging) { std::cout << "  SPAWNLASER() executed" << std::endl; }
}

void SpawnMissle(sf::Vector2f pos, float vel, float ang, float dam , int no_of_proj,  int team, Entity* sender, Entity *target, float size, int trail_length, float splash_radius, float terminal_vel, float power)
{
	if (eventLogging) { std::cout << "/SPAWNMISSLE()/" << std::endl; }

	sf::Vector2f t_vel;
	t_vel.x = cos(ang * std::numbers::pi / 180) * vel;
	t_vel.y = sin(ang * std::numbers::pi / 180) * vel;
	
	Missle newMissle;
	newMissle.spawn(pos, t_vel, dam, no_of_proj, team, sender, target, size, trail_length, splash_radius, terminal_vel, power);
	MissleArr.push_back(newMissle);

	if (eventLogging) { std::cout << "  SPAWNMISSLE() executed" << std::endl; }
}

void SpawnGameText(std::string Text, sf::Vector2f pos, sf::Color col, int size, float dur, float thickness, bool shadow)
{
	GameDisplayText newGT(Text, pos, col, size, dur, thickness, shadow);
	GameTextArr.push_back(newGT);
}

void SpawnDeadTank(sf::Vector2f pos, float ang, int team)
{
	DeadTank newDeadTank;
	newDeadTank.spawn(pos, ang, team);
	DeadTankArr.push_back(newDeadTank);
}

void SpawnButton(sf::Vector2f pos, sf::Vector2f size, std::string text, sf::Color colour, int action, int text_size) {
	Button newButton(pos, size, text, colour, action, text_size);
	ButtonArr.push_back(newButton);
}


void drawLine(sf::RenderWindow& wind, sf::Vector2f pos1, sf::Vector2f pos2, sf::Color col)
{
	static sf::VertexArray drawLine_line(sf::Lines, 2);
	drawLine_line[0].position = pos1;
	drawLine_line[0].color = col;
	drawLine_line[1].position = pos2;
	drawLine_line[1].color = col;

	wind.draw(drawLine_line);
}

void drawFilledCircle(sf::RenderWindow& myWindow, sf::Vector2f center, float radius, sf::Color col) {
	
	static sf::CircleShape circle;

	circle.setRadius(radius);
	circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
	circle.setFillColor(col);
	circle.setPosition(center);

	myWindow.draw(circle);
}

void drawCircle(sf::RenderWindow& myWindow, sf::Vector2f center, float radius, sf::Color col, int thickness) {
	sf::CircleShape circle(radius);

	circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
	circle.setOutlineColor(col); circle.setFillColor({ 0,0,0,0 }); circle.setOutlineThickness(thickness);
	circle.setPosition(center);
	
	myWindow.draw(circle);
}

void drawRegPolygon(sf::RenderWindow& myWindow, sf::Vector2f center, float radius, sf::Color col, int thickness, int sides, float rotation, bool fill) {
	static sf::CircleShape circle(radius);

	circle.setOrigin(circle.getGlobalBounds().width / 2, circle.getGlobalBounds().height / 2);
	circle.setOutlineColor(col); circle.setOutlineThickness(thickness);  circle.setFillColor({ 0,0,0,0 });
	if (fill){ circle.setFillColor(col); }
	circle.setPosition(center);
	circle.setPointCount(sides);
	circle.setRotation(rotation);

	myWindow.draw(circle);
}

void drawRect(sf::RenderWindow& myWindow, const sf::FloatRect rect, sf::Color col, int thickness)
{
	static sf::RectangleShape Rectangle;
	Rectangle.setPosition(rect.left, rect.top);
	Rectangle.setOutlineThickness(thickness);
	Rectangle.setSize({ rect.width, rect.height });
	Rectangle.setFillColor({ 0,0,0,0 });
	Rectangle.setOutlineColor(col);

	myWindow.draw(Rectangle);
}

void drawFilledRect(sf::RenderWindow& myWindow, const sf::FloatRect& rect, sf::Color col)
{
	static sf::RectangleShape drawFilledRect_Rect;
	drawFilledRect_Rect.setPosition(rect.left, rect.top);
	drawFilledRect_Rect.setSize({ rect.width, rect.height });
	drawFilledRect_Rect.setFillColor(col);
		
	myWindow.draw(drawFilledRect_Rect);
}

void drawArc(sf::RenderWindow& myWindow, sf::Vector2f center, float radius, sf::Color col, int thickness, float startAngle, float endAngle, int pointCount) {
	// Create a vertex array to represent the arc
	sf::VertexArray arc(sf::TriangleStrip, (pointCount + 1) * 2);

	// Convert angles to radians
	double M_PI = 3.14159265358979323846;
	float startRad = startAngle * (M_PI / 180.f);
	float endRad = endAngle * (M_PI / 180.f);
	float angleStep = (endRad - startRad) / pointCount;

	// Generate the points for the arc
	for (int i = 0; i <= pointCount; ++i) {
		float angle = startRad + i * angleStep;

		// Outer point
		float outerX = center.x + (radius + thickness / 2.f) * std::cos(angle);
		float outerY = center.y + (radius + thickness / 2.f) * std::sin(angle);
		arc[i * 2].position = sf::Vector2f(outerX, outerY);
		arc[i * 2].color = col;

		// Inner point
		float innerX = center.x + (radius - thickness / 2.f) * std::cos(angle);
		float innerY = center.y + (radius - thickness / 2.f) * std::sin(angle);
		arc[i * 2 + 1].position = sf::Vector2f(innerX, innerY);
		arc[i * 2 + 1].color = col;
	}

	// Draw the arc
	myWindow.draw(arc);
}


bool lineSegmentIntersection(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f q1, sf::Vector2f q2) {
	auto cross = [](sf::Vector2f v1, sf::Vector2f v2) {
		return v1.x * v2.y - v1.y * v2.x;
		};

	sf::Vector2f r = p2 - p1;
	sf::Vector2f s = q2 - q1;

	float rxs = cross(r, s);
	float qpxr = cross(q1 - p1, r);

	if (rxs == 0 && qpxr == 0) {
		// Collinear
		return false;
	}

	if (rxs == 0 && qpxr != 0) {
		// Parallel
		return false;
	}

	float t = cross(q1 - p1, s) / rxs;
	float u = qpxr / rxs;

	return (t >= 0 && t <= 1) && (u >= 0 && u <= 1);
}

bool checkLineCollision(sf::FloatRect rect, sf::Vector2f pos1, sf::Vector2f pos2) {
	// Check if either endpoint of the line is within the rectangle
	if (rect.contains(pos1) || rect.contains(pos2)) {
		return true;
	}

	// Get the four corners of the rectangle
	sf::Vector2f topLeft(rect.left, rect.top);
	sf::Vector2f topRight(rect.left + rect.width, rect.top);
	sf::Vector2f bottomLeft(rect.left, rect.top + rect.height);
	sf::Vector2f bottomRight(rect.left + rect.width, rect.top + rect.height);

	// Check intersection with each of the rectangle's edges
	if (lineSegmentIntersection(pos1, pos2, topLeft, topRight) ||
		lineSegmentIntersection(pos1, pos2, topRight, bottomRight) ||
		lineSegmentIntersection(pos1, pos2, bottomRight, bottomLeft) ||
		lineSegmentIntersection(pos1, pos2, bottomLeft, topLeft)) {
		return true;
	}

	return false;
}

void updateStageColour()
{
	StageColour = stage_Colour();
}

int getTankPop(int team)
{
	int num = 0;
	for (int i = 0; i < EntityArr.size(); i++) {
		if (EntityArr[i].ID == "tank" && EntityArr[i].team == team) {
			num++;
		}
	}
	return num;
}

int getFortPop(int team, bool captured)
{
	if (captured){
		return temp_Captured_Fort_Pop[team];
	}
	else {
		return temp_Fort_Pop[team];
	}
	
}

int getAverageTankAge(int team)
{
	float num = 0;
	float age = 0;
	for (int i = 0; i < EntityArr.size(); i++) {
		if (EntityArr[i].ID == "tank" && EntityArr[i].team == team) {
			num += 1;
			age += EntityArr[i].age * 1000 / FPS;
		}
	}
	if (num == 0) { return 0; }
	return (int)(round)(age / num);
}

int getSpecialTankPop(int team)
{
	return temp_Special_Tank_Pop[team];
}

int getSpecialFortPop(int team)
{
	return temp_Special_Fort_Pop[team];
}

int getTerritory(int team)
{
	int num = 0;
	for (int i = 0; i < TileArr.size(); i++) {
		if (TileArr[i].team == team) {
			num++;
		}
	}
	return num;
}

void UpdateTiles() 
{
	if (eventLogging) { std::cout << "###== Updating Tiles...; GameTick: " << game_ticks << "  ==###" << std::endl; }
	int size = TileArr.size();
	for (int i = 0; i < numberOfTeams; i++) {
		TeamTileNo[i] = 0;
		TeamTilePerc[i] = 0;
	}

	for (int i = 0; i < size; i++) {
		TileArr[i].update();
		if (TileArr[i].team != -1) { TeamTileNo[TileArr[i].team] += 1; }

	}

	for (int j = 0; j < TankDeathPositions.size(); j++) {
		float shortest_dis = 1000000;
		int closestTile_index, dis;
		closestTile_index = -1;
		for (int i = 0; i < size; i++) {
			sf::Vector2f temp_pos = { TankDeathPositions[j][0], TankDeathPositions[j][1] };
			sf::Vector2f temp2_pos = TileArr[i].pos;
			dis = displacement(temp2_pos, temp_pos);
			if (dis < shortest_dis) {
				closestTile_index = i;
				shortest_dis = dis;
			}
		}
		if (closestTile_index != -1) {
			TileArr[closestTile_index].tank_deaths += 1;
		}
	}

	for (int i = 0; i < size; i++) {
		TileArr[i].updateBorders();
	}

	for (int i = 0; i < numberOfTeams; i++) {
		TeamTilePerc[i] = TeamTileNo[i] * 100 / TileArr.size();
	}

	if (eventLogging) { std::cout << "  Tiles Updated" << std::endl; }


	TankDeathPositions.clear();
}

void InitTiles()
{
	TileArr.clear();
	double XX = GAME_MAP_WIDTH;
	double YY = GAME_MAP_HEIGHT;
	double size = Tiles_Size;
	int cx = 0; int cy = 0;
	float gx = 0, gy = 0;
	

	double x_fix = 1.2;

	for (double y = -size; y < YY + size; y += size) {
		cy++;
		cx = 0;
		for (double x = -size * x_fix; x < XX + (size * x_fix); x += (size * x_fix)) {
			cx++;
			gy = y;
			if (cy % 2 == 0) { gx = x - (size * x_fix / 4); }
			else             { gx = x + (size * x_fix / 4); }
			
			
			Tile newTile({gx, gy}, cx, cy);

			TileArr.push_back(newTile);
		}
	}
	for (int i = 0; i < TileArr.size(); i++) {
		TileArr[i].neighbors = getTileNeighbors(TileArr[i]);
	}
}

void DrawTiles()
{
	for (Tile &tile : TileArr) {
		//TileArr[i].draw();
		if (GameScreenRect.contains(tile.pos)) {
			tile.draw();
		}
	}
}

void drawThickLine(sf::RenderWindow& wind, sf::Vector2f pos1, sf::Vector2f pos2, float thickness, sf::Color color)
{
	sf::Vector2f dir = pos2 - pos1;
	float sqLen = dir.x * dir.x + dir.y * dir.y;

	// Check for zero-length lines
	if (sqLen < 1e-12f) return;

	// Compute inverse length once (avoids sqrt when possible)
	float invLen = 1.0f / std::sqrt(sqLen);
	dir.x *= invLen;
	dir.y *= invLen;

	// Calculate perpendicular direction (normalized)
	sf::Vector2f perp(-dir.y, dir.x);
	sf::Vector2f offset = perp * (thickness * 0.5f);

	// Define quad vertices (triangle strip order)
	sf::Vertex vertices[4] = {
		sf::Vertex(pos1 - offset, color),
		sf::Vertex(pos1 + offset, color),
		sf::Vertex(pos2 - offset, color),
		sf::Vertex(pos2 + offset, color)
	};

	// Draw the quad
	wind.draw(vertices, 4, sf::TriangleStrip);
}

void DemoGame(int type)
{
	if (eventLogging) { std::cout << "/DEMOGAME()/" << std::endl; }

	current_game_timer = 0;
	extra_population = 0;
	// Clear All Objects
	EntityArr.clear();
	LaserArr.clear();
	MissleArr.clear();
	TileArr.clear();
	ParticleArr.clear();
	GameTextArr.clear();
	DeadTankArr.clear();
	ButtonArr.clear();

	
	// Clear Team Statistics
	for (int i = 0; i < numberOfTeams; i++) {
		Tanks_Killed[i] = 0;
		Tanks_Lost[i] = 0;
		Forts_Destroyed[i] = 0;
		Forts_Lost[i] = 0;

		PvP_Tanks_Killed[i] = 0;
		PvP_Tanks_Lost[i] = 0;
	}

	// Json Graph Array
	TankPopArr.clear();
	FortPopArr.clear();
	CapturedFortPopArr.clear();
	CapturedFortRatioArr.clear();
	SpecialTankPopArr.clear();
	SpecialTankRatioArr.clear();
	SpecialFortPopArr.clear();
	SpecialFortRatioArr.clear();
	TanksKilledArr.clear();
	TanksLostArr.clear();
	AverageTankAgeArr.clear();
	TeamTerritoryArr.clear();
	

	
	GAME_MAP_WIDTH = 2500; GAME_MAP_HEIGHT = 2500;
	sf::FloatRect GameMapRect(0, 0, GAME_MAP_WIDTH, GAME_MAP_HEIGHT);
	type = rand() % 5;

	int repeat_no, repeat_no_max;
	repeat_no_max = 1'000;

	// Adjust game Map Size
	
	if (rand() % 2 == 0) {
		GAME_MAP_WIDTH = 3200; GAME_MAP_HEIGHT = 3200;
		GameMapRect = { 0, 0, GAME_MAP_WIDTH, GAME_MAP_HEIGHT };
	}
	if (rand() % 4 == 0) {
		GAME_MAP_WIDTH = 4000; GAME_MAP_HEIGHT = 4000;
		GameMapRect = { 0, 0, GAME_MAP_WIDTH, GAME_MAP_HEIGHT };
	}
	if (rand() % 3 == 0) {
		GAME_MAP_WIDTH = 5000; GAME_MAP_HEIGHT = 5000;
		GameMapRect = { 0, 0, GAME_MAP_WIDTH, GAME_MAP_HEIGHT };
	}
	
	float forts_per_team = (rand() % 10) + 5;
	if (GAME_MAP_WIDTH > 3200) { forts_per_team *= 1.5; }
	if (GAME_MAP_WIDTH > 4000) { forts_per_team *= 1.25; }


	// Random Map
	if (type == 0 || type == 3 || type == 4)
	{
		bool RandomMapDebug = false;
		if (eventLogging or RandomMapDebug) { std::cout << std::endl << std::endl << "  Demogame 1: Random game. Setting up..." << std::endl; }

		

		SpawnGameText("Random Game", { (float)(SCREEN_WIDTH / 2), (float)(SCREEN_HEIGHT / 2) }, { 255, 255, 255 }, 40, 5, 2, true);

		int team_no = (rand() % (numberOfTeams - 1)) + 2;
		if (RandomMapDebug) { std::cout << "Number of Teams: " + std::to_string(team_no) << std::endl; }
		

		
		// int forts_per_team = round((float)max_forts / (float)team_no);

		std::vector <int> team_arr;


		// Select Random Teams
		for (int i = 0; i < team_no; i++) {
			int newteam = rand() % numberOfTeams;
			bool repeat = false;


			for (int j = 0; j < team_arr.size(); j++) {
				if (team_arr[j] == newteam) {
					repeat = true;
				}
			}

			if (repeat) { i--; }
			else { team_arr.push_back(newteam); }
		}
		if (RandomMapDebug) { std::cout << "Random Teams Selected" << std::endl; }


		// Spawn Forts for the Teams
		std::vector <sf::Vector2f> centerpoint_arr;
		sf::Vector2f centerPoint, pos;
		bool center_repeat = true;
		float dx, dy, dis, ang;
		int size = 0;

		for (int i = 0; i < team_arr.size(); i++) {
			if (RandomMapDebug) { 
				std::cout << std::to_string(i) + ".." << std::endl; 
				std::cout << std::to_string(centerpoint_arr.size()) << std::endl;
			}
			// Check if team center positions are too close
			repeat_no = 0;
			size += 1;
			center_repeat = true;
			while (center_repeat) {
				center_repeat = false;
				if (repeat_no >= repeat_no_max) { EntityArr.clear(); std::cout << "Random Map Generation failed!" << std::endl;  DemoGame(); return; }
				repeat_no += 1;

				// Choose Center Point
				centerPoint = { (rand() % 100) * GAME_MAP_WIDTH / 100, (rand() % 100) * GAME_MAP_HEIGHT / 100 };

				for (int j = 0; j < centerpoint_arr.size(); j++) {
					dx = centerPoint.x - centerpoint_arr[j].x;
					dy = centerPoint.y - centerpoint_arr[j].y;
					dis = std::sqrt(dx * dx + dy * dy);

					if (dis < 100) {
						center_repeat = true;
						if (RandomMapDebug) { std::cout << "Repeating Team: " + std::to_string(team_arr[i]) << std::endl; }
					}
				}
				if (centerpoint_arr.size() == 0) { center_repeat = false; }

				if (!center_repeat) { centerpoint_arr.push_back(centerPoint); }
			}
			
			
		}

		// debug
		if (RandomMapDebug) {
			std::cout << "Size: " + std::to_string(size) << std::endl;
			std::cout << "Number of Centerpoints: " + std::to_string(centerpoint_arr.size()) << std::endl;
			for (int k = 0; k < centerpoint_arr.size(); k++) {
				std::cout << std::to_string(centerpoint_arr[k].x) + "," + std::to_string(centerpoint_arr[k].y) << std::endl;
			}
		}
		

		// Spawn all the Forts for each team
		for (int j = 0; j < forts_per_team; j++) {
			bool repeat = true;
			repeat_no = 0;
			
			for (int i = 0; i < team_arr.size(); i++) {
				repeat = true;
				// Calculating the Position for each Fort
				while (repeat) {
					repeat_no += 1;
					if (repeat_no >= repeat_no_max) { EntityArr.clear(); std::cout << "Random Map Fort Generation Error!" << std::endl; DemoGame(); return; }

					dis = (rand() % 500 * GAME_MAP_WIDTH / 2500) * pow(numberOfTeams / team_no, .75);
					ang = rand() % 360;

					dx = cos(ang * std::numbers::pi / 180) * dis;
					dy = sin(ang * std::numbers::pi / 180) * dis;

					pos = { dx,dy };
					pos += centerpoint_arr[i];

					if (GameMapRect.contains(pos)) { repeat = false; }

					// Make Sure Forts are not too close
					for (int k = 0; k < EntityArr.size(); k++) {
						if (EntityArr[k].ID == "fort") {
							dx = pos.x - EntityArr[k].pos[0];
							dy = pos.y - EntityArr[k].pos[1];

							dis = std::sqrt(dx * dx + dy * dy);
							if (dis <= Fort_RANGE * 1.25 && EntityArr[k].team != team_arr[i]) { repeat = true; break; }
							if (dis < Fort_RANGE * .33 && EntityArr[k].team == team_arr[i]) { repeat = true; break; }

						}
					}

				}


				SpawnFort(pos, team_arr[i]);
			}
			
				
		}
			
		

		
		if (eventLogging) { std::cout << "    Demogame 1: Random game. Setup Complete." << std::endl; }
	}

	// 1 vs 1 [2 teams]
	if (type == 1) {
		if (eventLogging) { std::cout << "  Demogame 2: 1 VS 1. Setting up..." << std::endl; }

		SpawnGameText("1 VS 1", { (float)(SCREEN_WIDTH / 2), (float)(SCREEN_HEIGHT / 2) }, { 255, 255, 255 }, 40, 5, 3, true);

		std::vector <int> team_arr;
		int team_no = 2;
		float arc_range = 360.f / team_no;
		float angle_offset = rand() % 360;


		// Select Random Teams
		for (int i = 0; i < team_no; i++) {
			int newteam = rand() % numberOfTeams;
			bool repeat = false;


			for (int j = 0; j < team_arr.size(); j++) {
				if (team_arr[j] == newteam) {
					repeat = true;
				}
			}
			if (repeat) { i--; }
			else { team_arr.push_back(newteam); }
		}

		
		// int forts_per_team = float(max_forts / team_no) + 1;

		sf::Vector2f fort_pos;
		sf::Vector2f center_pos = { GAME_MAP_WIDTH / 2,GAME_MAP_HEIGHT / 2 };

		float dx, dy, ang, dis, team_ang;
		sf::Vector2f v_dis;



		// Soawn Forts
		for (int i = 0; i < forts_per_team; i++) {
			for (int j = 0; j < team_arr.size(); j++) {
				bool repeat = true;  repeat_no = 0;
				while (repeat) {
					repeat_no += 1;
					if (repeat_no >= repeat_no_max) { EntityArr.clear(); std::cout << "1 VS 1 Map Generation Failed" << std::endl; DemoGame(); return; }


					team_ang = (arc_range * j) + angle_offset;
					ang = team_ang + (rand() % (int)arc_range);

					dis = rand() % (int)(pow(pow(GAME_MAP_WIDTH / 2, 2) + pow(GAME_MAP_HEIGHT / 2, 2), .5)); // maximim distance is the distance from the center to the corner.
					dx = cos(ang * std::numbers::pi / 180) * dis + center_pos.x;
					dy = sin(ang * std::numbers::pi / 180) * dis + center_pos.y;

					fort_pos = { dx, dy };


					if (GameMapRect.contains(fort_pos)) { repeat = false; }



					for (int k = 0; k < EntityArr.size(); k++) {
						if (EntityArr[k].ID == "fort") {
							dx = EntityArr[k].pos[0] - fort_pos.x;
							dy = EntityArr[k].pos[1] - fort_pos.y;

							dis = std::sqrt(dx * dx + dy * dy);

							if (team_arr[j] != EntityArr[k].team) { if (dis < Fort_RANGE * 1.1) { repeat = true; } }
							else { if (dis < Fort_RANGE * .4) { repeat = true; } }
						}
					}
				}

				SpawnFort(fort_pos, team_arr[j]);

			}
		}

		if (eventLogging) { std::cout << "    Demogame 2: 1 VS 1. Setup Complete." << std::endl; }
	}

	// RoundTable Map
	if (type == 2) {
		if (eventLogging) { std::cout << "  Demogame 3: Roundtable Game. Setting up..." << std::endl; }

		SpawnGameText("Roundable Game", { (float)(SCREEN_WIDTH / 2), (float)(SCREEN_HEIGHT / 2) }, { 255, 255, 255 }, 40, 5, 3, true);

		std::vector <int> team_arr;
		int team_no = (rand() % (numberOfTeams - 2)) + 3;
		float arc_range = 360.f / team_no;
		float angle_offset = rand() % 360;

		

		// Select Random Teams
		for (int i = 0; i < team_no; i++) {
			int newteam = rand() % numberOfTeams;
			bool repeat = false;


			for (int j = 0; j < team_arr.size(); j++) {
				if (team_arr[j] == newteam) {
					repeat = true;
				}
			}
			if (repeat) { i--; }
			else { team_arr.push_back(newteam); }
		}

		
		// int forts_per_team = float(max_forts / team_no) + 1;

		sf::Vector2f fort_pos;
		sf::Vector2f center_pos = { GAME_MAP_WIDTH / 2,GAME_MAP_HEIGHT / 2 };

		float dx, dy, ang, dis, team_ang;
		sf::Vector2f v_dis;

		
		
		// Spawn Forts
		for (int i = 0; i < forts_per_team; i++) {
			for (int j = 0; j < team_arr.size(); j++) {
				bool repeat = true;  repeat_no = 0;
				while (repeat) {
					repeat_no += 1;
					if (repeat_no >= repeat_no_max) { EntityArr.clear(); std::cout << "RoundTable Map Generation Failed!" << std::endl; DemoGame(); return; }


					team_ang = (arc_range * j) + angle_offset;
					ang = team_ang + (rand() % (int)arc_range);

					dis = rand() % (int)(pow(pow(GAME_MAP_WIDTH / 2, 2) + pow(GAME_MAP_HEIGHT / 2, 2), .5)); // maximim distance is the distance from the center to the corner.
					dx = cos(ang * std::numbers::pi / 180) * dis + center_pos.x;
					dy = sin(ang * std::numbers::pi / 180) * dis + center_pos.y;

					fort_pos = { dx, dy };
					

					if (GameMapRect.contains(fort_pos)) { repeat = false; }

					

					for (int k = 0; k < EntityArr.size(); k++) {
						if (EntityArr[k].ID == "fort") {
							dx = EntityArr[k].pos[0] - fort_pos.x;
							dy = EntityArr[k].pos[1] - fort_pos.y;
							
							dis = std::sqrt(dx * dx + dy * dy);

							if (team_arr[j] != EntityArr[k].team) {if (dis < Fort_RANGE * 1.1) { repeat = true; }}
							else { if (dis < Fort_RANGE * .25) { repeat = true; } }
						}
					}
				}

				SpawnFort(fort_pos, team_arr[j]);
				
			}
		}

		if (eventLogging) { std::cout << "    Demogame 3: Roundtable Game. Setup Complete." << std::endl; }
	}

	// Set all Forts to Immediately spawn tanks
	for (int i = 0; i < EntityArr.size(); i++) {
		if (EntityArr[i].ID == "fort") {
			EntityArr[i].Tank_spawn_timer = EntityArr[i].max_Tank_spawn_time;
		}
	}

	// Identify and Make Center Fort Special
	for (int team = 0; team < numberOfTeams; team++) {
		sf::Vector2f teamCenter = { 0, 0 };
		float fortCount = 0;

		// Calculate the center position of all forts for this team
		for (auto& entity : EntityArr) {
			if (entity.ID == "fort" && entity.team == team) {
				teamCenter.x += entity.pos[0];
				teamCenter.y += entity.pos[1];
				fortCount += 1;
			}
		}

		if (fortCount > 0) {
			teamCenter.x /= fortCount;
			teamCenter.y /= fortCount;

			// Find the Fort closest to the center
			Entity* closestFort = nullptr;
			float closestDistance = 100'000;

			for (auto& entity : EntityArr) {
				if (entity.ID == "fort" && entity.team == team) {
					sf::Vector2f entity_pos = { entity.pos[0], entity.pos[1] };
					float distance = displacement(entity_pos, teamCenter);
					if (distance < closestDistance) {
						closestDistance = distance;
						closestFort = &entity;
					}
				}
			}

			// Mark the closest Fort as special
			if (closestFort) {
				closestFort->fort_level = 1;
			}
		}
	}
	InitTiles();
	UpdateTiles();

	loadGameButtons();

	if (eventLogging) { std::cout << "  DEMOGAME() executed" << std::endl; }
}



void updateWind() {
	if (!WIND_Physics) { return; }
	float scalarWind;
	float maxWindVel = .05 * WIND_max_speed_factor;
	float windStrength = WIND_strength_factor;

	
	float factor;
	float vel = (((float)((rand() % 100) + 1) / 10000) - 0.005) * windStrength;
	float ang = rand() % 360;
	wind_vel.x += cos(ang * 3.14159 / 180) * vel;
	wind_vel.y += sin(ang * 3.14159 / 180) * vel;
	float dx = wind_vel.x; float dy = wind_vel.y;
	scalarWind = std::sqrt(dx * dx + dy * dy);
	if (scalarWind > maxWindVel) {
		factor = maxWindVel / scalarWind;
		wind_vel *= factor;
	}
}

void loadGameButtons() {
	SpawnButton({ 10,SCREEN_HEIGHT - 40 }, { 30,25 }, "QUIT", { 200,20,40 }, 0, 16);
	SpawnButton({ 50, SCREEN_HEIGHT - 40 }, { 50,25 }, "RANDOM", { 20,40,200 }, 1, 16);
	SpawnButton({ 110, SCREEN_HEIGHT - 40 }, { 50, 25 }, "DELETE", { 40,40,40 }, numberOfTeams + 2, 16);
	SpawnButton({ 170, SCREEN_HEIGHT - 40 }, { 75, 25 }, "NULL TEAM", { 200,200,200 }, numberOfTeams + 3, 16);
	

	
	for (int i = 0; i < numberOfTeams; i++) {
		SpawnButton({ SCREEN_WIDTH - ((i + 1) * 30), SCREEN_HEIGHT - 40 }, { 20, 25 }, std::to_string(numberOfTeams - i), colorArr[numberOfTeams - i - 1], (numberOfTeams - i - 1) + 2, 16);
	}
}

void updateStats() {
	int num[numberOfTeams];
	int num2[numberOfTeams];
	// Tank Pop
	for (int team = 0; team < numberOfTeams; team++) {
		num[team] = 0;
		for (int i = 0; i < EntityArr.size(); i++) {
			if (EntityArr[i].ID == "tank" && EntityArr[i].team == team) {
				num[team]++;
			}
		}
		temp_Tank_Pop[team] = num[team];
	}
	// Fort Pop
	for (int team = 0; team < numberOfTeams; team++) {
		num[team] = 0;
		num2[team] = 0;
		for (int i = 0; i < EntityArr.size(); i++) {
			if (EntityArr[i].ID == "fort" && EntityArr[i].team == team) {
				num[team]++;
				if (EntityArr[i].Tank_spawn_timer < 0) { num2[team]++; } // Tally for Captured Forts
			}
		}
		temp_Fort_Pop[team] = num[team];
		temp_Captured_Fort_Pop[team] = num2[team];
	}
	// Special Tank Pop
	for (int team = 0; team < numberOfTeams; team++) {
		num[team] = 0;
		for (int i = 0; i < EntityArr.size(); i++) {
			if (EntityArr[i].ID == "tank" && EntityArr[i].team == team && EntityArr[i].level != 0) {
				num[team]++;
			}
		}
		temp_Special_Tank_Pop[team] = num[team];
	}
	// Special Fort Pop
	for (int team = 0; team < numberOfTeams; team++) {
		num[team] = 0;
		for (int i = 0; i < EntityArr.size(); i++) {
			if (EntityArr[i].ID == "fort" && EntityArr[i].team == team && EntityArr[i].fort_level != 0) {
				num[team]++;
			}
		}
		temp_Special_Fort_Pop[team] = num[team];
	}

	
	

}

void saveJSONData()
{
	json jsonArray;
	std::string fileName;
	std::ofstream outputFile;

	// Ensure the "Game Data" directory exists
	const std::string folderName = "Game Data";
	if (!Folder_Exists(folderName)) {
		_mkdir(folderName.c_str());
	}

	// Helper lambda to prepend folder path
	auto makePath = [&](const std::string& name) {
		return folderName + "/" + name;
	};

	// Tank Population Array
	jsonArray = json(TankPopArr);
	fileName = makePath("TankPop.json");
	outputFile.open(fileName);
	if (outputFile.is_open()) {
		outputFile << jsonArray.dump(4);
		outputFile.close();
	}

	// Fort Population Array
	jsonArray = json(FortPopArr);
	fileName = makePath("FortPop.json");
	outputFile.open(fileName);
	if (outputFile.is_open()) {
		outputFile << jsonArray.dump(4);
		outputFile.close();
	}

	// Captured Fort Population Array
	jsonArray = json(CapturedFortPopArr);
	fileName = makePath("CapturedFortPop.json");
	outputFile.open(fileName);
	if (outputFile.is_open()) {
		outputFile << jsonArray.dump(4);
		outputFile.close();
	}

	// Captured Fort Ratio Array
	jsonArray = json(CapturedFortRatioArr);
	fileName = makePath("CapturedFortRatio.json");
	outputFile.open(fileName);
	if (outputFile.is_open()) {
		outputFile << jsonArray.dump(4);
		outputFile.close();
	}

	// Special Tank Population Array
	jsonArray = json(SpecialTankPopArr);
	fileName = makePath("SpecialTankPop.json");
	outputFile.open(fileName);
	if (outputFile.is_open()) {
		outputFile << jsonArray.dump(4);
		outputFile.close();
	}

	// Special Tank Ratio Array
	jsonArray = json(SpecialTankRatioArr);
	fileName = makePath("SpecialTankRatio.json");
	outputFile.open(fileName);
	if (outputFile.is_open()) {
		outputFile << jsonArray.dump(4);
		outputFile.close();
	}

	// Special Fort Pop Arr
	jsonArray = json(SpecialFortPopArr);
	fileName = makePath("SpecialFortPop.json");
	outputFile.open(fileName);
	if (outputFile.is_open()) {
		outputFile << jsonArray.dump(4);
		outputFile.close();
	}

	// Special Fort Ratio Arr
	jsonArray = json(SpecialFortRatioArr);
	fileName = makePath("SpecialFortRatio.json");
	outputFile.open(fileName);
	if (outputFile.is_open()) {
		outputFile << jsonArray.dump(4);
		outputFile.close();
	}

	// Tanks Killed Array
	jsonArray = json(TanksKilledArr);
	fileName = makePath("TanksKilled.json");
	outputFile.open(fileName);
	if (outputFile.is_open()) {
		outputFile << jsonArray.dump(4);
		outputFile.close();
	}

	// Tanks Lost Array
	jsonArray = json(TanksLostArr);
	fileName = makePath("TanksLost.json");
	outputFile.open(fileName);
	if (outputFile.is_open()) {
		outputFile << jsonArray.dump(4);
		outputFile.close();
	}

	// Average Tank Age Array
	jsonArray = json(AverageTankAgeArr);
	fileName = makePath("AverageTankAge.json");
	outputFile.open(fileName);
	if (outputFile.is_open()) {
		outputFile << jsonArray.dump(4);
		outputFile.close();
	}

	// Team Territory Array
	jsonArray = json(TeamTerritoryArr);
	fileName = makePath("Territory.json");
	outputFile.open(fileName);
	if (outputFile.is_open()) {
		outputFile << jsonArray.dump(4);
		outputFile.close();
	}
}


sf::Vector2f scaleVector(sf::Vector2f& vector, float magnitude) {
	sf::Vector2f newVector = { 0,0 };
	float Old_magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);
	return { vector.x * magnitude / Old_magnitude, vector.y * magnitude / Old_magnitude };
}

float displacement(sf::Vector2f& vec_1, sf::Vector2f&vec_2) {
	sf::Vector2f diff_vec = vec_2 - vec_1;
	return  std::sqrt(diff_vec.x * diff_vec.x + diff_vec.y * diff_vec.y);
}


void saveGameState(const std::string& filename) {
	json j;

	// Iterate over each Entity in the global EntityArr vector
	for (const auto& entity : EntityArr) {
		json entityJson;

		// Save the necessary fields; modify as needed:
		entityJson["ID"] = entity.ID;
		entityJson["uniqueID"] = entity.uniqueID;
		entityJson["team"] = entity.team;
		entityJson["hp"] = entity.hp;
		entityJson["max_hp"] = entity.max_hp;
		entityJson["ang"] = entity.ang;

		// Save position, velocity, and acceleration as arrays
		entityJson["pos"] = { entity.pos[0], entity.pos[1] };
		entityJson["vel"] = { entity.vel[0], entity.vel[1] };
		entityJson["acc"] = { entity.acc[0], entity.acc[1] };

		// Append this entity's JSON data to the main JSON object
		j["entities"].push_back(entityJson);
	}

	// Write the JSON data to a file with pretty formatting
	std::ofstream outFile(filename);
	if (outFile.is_open()) {
		outFile << std::setw(4) << j;
		outFile.close();
	}
	else {
		std::cerr << "Could not open file " << filename << " for writing." << std::endl;
	}
}




std::string getDateString() {
	std::time_t now = std::time(nullptr);
	std::tm localTime;
	localtime_s(&localTime, &now);  // Use localtime_s instead of localtime

	std::ostringstream oss;
	oss << (localTime.tm_year + 1900) << "-"
		<< std::setw(2) << std::setfill('0') << (localTime.tm_mon + 1) << "-"
		<< std::setw(2) << std::setfill('0') << localTime.tm_mday;
	return oss.str();
}

std::string getTimeString() {
	std::time_t now = std::time(nullptr);
	std::tm localTime;
	localtime_s(&localTime, &now);  // Use localtime_s here as well

	std::ostringstream oss;
	oss << std::setw(2) << std::setfill('0') << localTime.tm_hour << "~"
		<< std::setw(2) << std::setfill('0') << localTime.tm_min << "~"
		<< std::setw(2) << std::setfill('0') << localTime.tm_sec;
	return oss.str();
}



std::string OpenFileDialog(const char* filter, HWND owner) {
	OPENFILENAMEA ofn;       // Common dialog box structure
	char fileName[MAX_PATH] = ""; // Buffer for file name

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

	// Display the Open dialog box.
	if (GetOpenFileNameA(&ofn) == TRUE) {
		return std::string(fileName);
	}
	return std::string();
}

Entity* checkEntity(Entity* entity) {
	__try {
		volatile int dummy = entity->uniqueID; // Attempt access.
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		std::cout << "Error: Invalid Sender sent to SpawnLaser() function. Using Null Pointer" << std::endl;
		return nullptr;
	}
	return entity;
}

std::vector<Tile*> getTileNeighbors(Tile& tile) {
	static const int even_offsets[6][2] = { {-1,-1}, {0,-1}, {1,0}, {0,1}, {-1,1}, {-1,0} };
	static const int odd_offsets[6][2] = { {0,-1}, {1,-1}, {1,0}, {1,1}, {0,1}, {-1,0} };

	std::vector<Tile*> neighbors;
	const int (*offsets)[2] = (tile.grid_y % 2 == 0) ? even_offsets : odd_offsets;

	for (int i = 0; i < 6; ++i) {
		int nx = tile.grid_x + offsets[i][0];
		int ny = tile.grid_y + offsets[i][1];
		// Find the tile in TileArr with (nx, ny)
		for (Tile& t : TileArr) {
			if (t.grid_x == nx && t.grid_y == ny) {
				neighbors.push_back(&t);
				break;
			}
		}
	}
	return neighbors;
}

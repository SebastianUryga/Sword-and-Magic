#include"GuiHandler.h"

Graphics2& graphics2 = Graphics2::Get();

Graphics2::Graphics2()
{
}

Graphics2::~Graphics2()
{
}

void Graphics2::init()
{
	creaturesTextures[Monster::MonsterType::NO_CREATURE] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::NO_CREATURE].portrait = std::make_shared<sf::Texture>();
	creaturesTextures[Monster::MonsterType::NO_CREATURE].portrait->loadFromFile("Textures/No_Creature_portrait.png");
	creaturesTextures[Monster::MonsterType::ORK1] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::ORK1].Load("ORK_01");
	creaturesTextures[Monster::MonsterType::ORK2] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::ORK2].Load("ORK_02");
	creaturesTextures[Monster::MonsterType::ORK3] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::ORK3].Load("ORK_03");

	creaturesTextures[Monster::MonsterType::TROLL1] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::TROLL1].Load("Troll_01_1");
	creaturesTextures[Monster::MonsterType::TROLL2] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::TROLL2].Load("Troll_02_1");
	creaturesTextures[Monster::MonsterType::TROLL3] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::TROLL3].Load("Troll_03_1");

	creaturesTextures[Monster::MonsterType::KNIGHT1] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::KNIGHT1].Load("Knight_01");
	creaturesTextures[Monster::MonsterType::KNIGHT2] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::KNIGHT2].Load("Knight_02");
	creaturesTextures[Monster::MonsterType::KNIGHT3] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::KNIGHT3].Load("Knight_03");
	
	creaturesTextures[Monster::MonsterType::ELF1] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::ELF1].Load("Elf_01_");
	creaturesTextures[Monster::MonsterType::ELF2] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::ELF2].Load("Elf_02_");
	creaturesTextures[Monster::MonsterType::ELF3] = *std::make_shared<CreatureTexture>();
	creaturesTextures[Monster::MonsterType::ELF3].Load("Elf_03_");

	backgroundsTextures[Background::BACKGROUND1] = std::make_shared<sf::Texture>();
	backgroundsTextures[Background::BACKGROUND1]->loadFromFile("Textures/game_background_1/game_background_1.png");
	backgroundsTextures[Background::BACKGROUND2] = std::make_shared<sf::Texture>();
	backgroundsTextures[Background::BACKGROUND2]->loadFromFile("Textures/game_background_2/game_background_2.png");
	/*backgroundsTextures[Background::BACKGROUND3] = std::make_shared<sf::Texture>();
	backgroundsTextures[Background::BACKGROUND3]->loadFromFile("Textures/game_background_3/game_background_3.png");
	*/
	this->arrow.loadFromFile("Textures/arrow.png");
	this->magicBulet.loadFromFile("Textures/magicBulet.png");

	this->spellIcons[Spell::SpellType::WEEKNES] = sf::IntRect(74 * 0, 74 * 1, 74, 74);
	this->spellIcons[Spell::SpellType::SHIELD] = sf::IntRect(74 * 2, 74 * 2, 74, 74);
	this->spellIcons[Spell::SpellType::HASTE] = sf::IntRect(74 * 2, 74 * 0, 74, 74);
	this->spellIcons[Spell::SpellType::CURSE] = sf::IntRect(74 * 1, 74 * 1, 74, 74);
	this->spellIcons[Spell::SpellType::BLESS] = sf::IntRect(74 * 1, 74 * 0, 74, 74);
	this->spellIcons[Spell::SpellType::SLOW] = sf::IntRect(74 * 0, 74 * 0, 74, 74);
	this->spellIcons[Spell::SpellType::TURN_TO_STONE] = sf::IntRect(74 * 1, 74 * 2, 74, 74);
	this->spellIcons[Spell::SpellType::COUNTER_STRIKE] = sf::IntRect(74 * 0, 74 * 2, 74, 74);
	this->spellIcons[Spell::SpellType::STRENGTH] = sf::IntRect(74 * 2, 74 * 1, 74, 74);
	this->spellIcons[Spell::SpellType::NONE] = sf::IntRect(0 , 0, 0, 0);
	
	
	
	this->battleEffects[Spell::SpellType::WEEKNES] = std::make_shared<sf::Texture>();
	this->battleEffects[Spell::SpellType::WEEKNES]->loadFromFile("Textures/BattleEffects/broke sword.png");
	this->battleEffects[Spell::SpellType::BLESS] = std::make_shared<sf::Texture>();
	this->battleEffects[Spell::SpellType::BLESS]->loadFromFile("Textures/BattleEffects/lidership.png");
	this->battleEffects[Spell::SpellType::TURN_TO_STONE] = std::make_shared<sf::Texture>();
	this->battleEffects[Spell::SpellType::TURN_TO_STONE]->loadFromFile("Textures/BattleEffects/blind.png");
	this->battleEffects[Spell::SpellType::CURSE] = std::make_shared<sf::Texture>();
	this->battleEffects[Spell::SpellType::CURSE]->loadFromFile("Textures/BattleEffects/skull.png");
	this->battleEffects[Spell::SpellType::SHIELD] = std::make_shared<sf::Texture>();
	this->battleEffects[Spell::SpellType::SHIELD]->loadFromFile("Textures/BattleEffects/shield.png");
	this->battleEffects[Spell::SpellType::HASTE] = std::make_shared<sf::Texture>();
	this->battleEffects[Spell::SpellType::HASTE]->loadFromFile("Textures/BattleEffects/haste.png");
	this->battleEffects[Spell::SpellType::COUNTER_STRIKE] = std::make_shared<sf::Texture>();
	this->battleEffects[Spell::SpellType::COUNTER_STRIKE]->loadFromFile("Textures/BattleEffects/swords.png");
	this->battleEffects[Spell::SpellType::SLOW] = std::make_shared<sf::Texture>();
	this->battleEffects[Spell::SpellType::SLOW]->loadFromFile("Textures/BattleEffects/mud.png");
	this->battleEffects[Spell::SpellType::STRENGTH] = std::make_shared<sf::Texture>();
	this->battleEffects[Spell::SpellType::STRENGTH]->loadFromFile("Textures/BattleEffects/sword.png");



	this->battleEffectsSheet = std::make_shared<sf::Texture>();
	this->allSpellIcons = std::make_shared<sf::Texture>();
	this->image.loadFromFile("Textures/spellIkons.png");
	this->allSpellIcons->loadFromImage(this->image);

	this->image.loadFromFile("Textures/BattleEffects.png");
	this->battleEffectsSheet->loadFromImage(this->image);

}

sf::IntRect Graphics2::selectSpellIcon(Spell type)
{
	return Graphics2::Get().spellIcons[type.spell];
}

Graphics2& Graphics2::Get()
{
	static Graphics2 gr;
	return gr;
}

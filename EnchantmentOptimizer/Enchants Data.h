#pragma once
#include <vector>
#include <map>

#include "EnchantInfo.h"

enum class Enchant
{
    Infinity = 0,
    AquaAffinity,
    BaneOfArthropods,
    BlastProtection,
    Channeling,
    CurseOfBinding,
    CurseOfVanishing,
    DepthStrider,
    Efficiency,
    FeatherFalling,
    FireAspect,
    FireProtection,
    Flame,
    Fortune,
    FrostWalker,
    Impaling,
    Knockback,
    Looting,
    Loyalty,
    LuckOfTheSea,
    Lure,
    Mending,
    Multishot,
    Piercing,
    Power,
    ProjectileProtection,
    Protection,
    Punch,
    QuickCharge,
    Respiration,
    Riptide,
    Sharpness,
    SilkTouch,
    Smite,
    SoulSpeed,
    SweepingEdge,
    Thorns,
    Unbreaking,
};

inline std::vector<EnchantInfo> enchants = { EnchantInfo(1, 8, 4),
EnchantInfo(1,4,2),
EnchantInfo(5,2,1),
EnchantInfo(4,4,2),
EnchantInfo(1,8,4),
EnchantInfo(1,8,4),
EnchantInfo(1,8,4),
EnchantInfo(3,4,2),
EnchantInfo(5,1,1),
EnchantInfo(4,2,1),
EnchantInfo(2,4,2),
EnchantInfo(4,2,1),
EnchantInfo(1,4,2),
EnchantInfo(3,4,2),
EnchantInfo(2,3,2),
EnchantInfo(5,4,2),
EnchantInfo(2,2,1),
EnchantInfo(3,4,2),
EnchantInfo(3,2,1),
EnchantInfo(3,4,2),
EnchantInfo(3,4,2),
EnchantInfo(1,4,2),
EnchantInfo(1,4,2),
EnchantInfo(4,1,1),
EnchantInfo(5,1,1),
EnchantInfo(4,2,1),
EnchantInfo(4,1,1),
EnchantInfo(2,4,2),
EnchantInfo(3,2,1),
EnchantInfo(3,4,2),
EnchantInfo(3,4,2),
EnchantInfo(5,1,1),
EnchantInfo(1,8,4),
EnchantInfo(5,2,1),
EnchantInfo(3,8,4),
EnchantInfo(3,4,2),
EnchantInfo(3,8,4),
EnchantInfo(3,2,1)
};

inline std::map<std::string, Enchant> enchantsStrMap = { {"Infinity", Enchant::Infinity},
                                                    {"Aqua Affinity", Enchant::AquaAffinity},
                                                    {"Bane of Arthropods", Enchant::BaneOfArthropods},
                                                    {"Blast Protection", Enchant::BlastProtection},
                                                    {"Channeling", Enchant::Channeling},
                                                    {"Curse of Binding", Enchant::CurseOfBinding},
                                                    {"Curse of Vanishing", Enchant::CurseOfVanishing},
                                                    {"Depth Strider", Enchant::DepthStrider},
                                                    {"Efficiency", Enchant::Efficiency},
                                                    {"Feather Falling", Enchant::FeatherFalling},
                                                    {"Fire Aspect", Enchant::FireAspect},
                                                    {"Fire Protection", Enchant::FireProtection},
                                                    {"Flame", Enchant::Flame},
                                                    {"Fortune", Enchant::Fortune},
                                                    {"Frost Walker", Enchant::FrostWalker},
                                                    {"Impaling", Enchant::Impaling},
                                                    {"Knockback", Enchant::Knockback},
                                                    {"Looting", Enchant::Looting},
                                                    {"Loyalty", Enchant::Loyalty},
                                                    {"Luck of the Sea", Enchant::LuckOfTheSea},
                                                    {"Lure", Enchant::Lure},
                                                    {"Mending", Enchant::Mending},
                                                    {"Multishot", Enchant::Multishot},
                                                    {"Piercing", Enchant::Piercing},
                                                    {"Power", Enchant::Power},
                                                    {"Projectile Protection", Enchant::ProjectileProtection},
                                                    {"Protection", Enchant::Protection},
                                                    {"Punch", Enchant::Punch},
                                                    {"Quick Charge", Enchant::QuickCharge},
                                                    {"Respiration", Enchant::Respiration},
                                                    {"Riptide", Enchant::Riptide},
                                                    {"Sharpness", Enchant::Sharpness},
                                                    {"Silk Touch", Enchant::SilkTouch},
                                                    {"Smite", Enchant::Smite},
                                                    {"Soul Speed", Enchant::SoulSpeed},
                                                    {"Sweeping Edge", Enchant::SweepingEdge},
                                                    {"Thorns", Enchant::Thorns},
                                                    {"Unbreaking", Enchant::Unbreaking} };

inline std::map<Enchant, std::string> enchToStr = { {Enchant::Infinity, "Infinity"},
                                                    {Enchant::AquaAffinity, "Aqua Affinity"},
                                                    {Enchant::BaneOfArthropods, "Bane of Arthropods"},
                                                    {Enchant::BlastProtection, "Blast Protection"},
                                                    {Enchant::Channeling, "Channeling"},
                                                    {Enchant::CurseOfBinding, "Curse of Binding"},
                                                    {Enchant::CurseOfVanishing, "Curse of Vanishing"},
                                                    {Enchant::DepthStrider, "Depth Strider"},
                                                    {Enchant::Efficiency, "Efficiency"},
                                                    {Enchant::FeatherFalling, "Feather Falling"},
                                                    {Enchant::FireAspect, "Fire Aspect"},
                                                    {Enchant::FireProtection, "Fire Protection"},
                                                    {Enchant::Flame, "Flame"},
                                                    {Enchant::Fortune, "Fortune"},
                                                    {Enchant::FrostWalker, "Frost Walker"},
                                                    {Enchant::Impaling, "Impaling"},
                                                    {Enchant::Knockback, "Knockback"},
                                                    {Enchant::Looting, "Looting"},
                                                    {Enchant::Loyalty, "Loyalty"},
                                                    {Enchant::LuckOfTheSea, "Luck of the Sea"},
                                                    {Enchant::Lure, "Lure"},
                                                    {Enchant::Mending, "Mending"},
                                                    {Enchant::Multishot, "Multishot"},
                                                    {Enchant::Piercing, "Piercing"},
                                                    {Enchant::Power, "Power"},
                                                    {Enchant::ProjectileProtection, "Projectile Protection"},
                                                    {Enchant::Protection, "Protection"},
                                                    {Enchant::Punch, "Punch"},
                                                    {Enchant::QuickCharge, "Quick Charge"},
                                                    {Enchant::Respiration, "Respiration"},
                                                    {Enchant::Riptide, "Riptide"},
                                                    {Enchant::Sharpness, "Sharpness"},
                                                    {Enchant::SilkTouch, "Silk Touch"},
                                                    {Enchant::Smite, "Smite"},
                                                    {Enchant::SoulSpeed, "Soul Speed"},
                                                    {Enchant::SweepingEdge, "Sweeping Edge"},
                                                    {Enchant::Thorns, "Thorns"},
                                                    {Enchant::Unbreaking, "Unbreaking"} };

/*std::map<std::string, EnchantInfo> enchants = { {"Infinity", EnchantInfo(1,8,4)},
                                                    {"Aqua Affinity", EnchantInfo(1,4,2)},
                                                    {"Bane of Arthropods", EnchantInfo(5,2,1)},
                                                    {"Blast Protection", EnchantInfo(4,4,2)},
                                                    {"Channeling", EnchantInfo(1,8,4)},
                                                    {"Curse of Binding", EnchantInfo(1,8,4)},
                                                    {"Curse of Vanishing", EnchantInfo(1,8,4)},
                                                    {"Depth Strider", EnchantInfo(3,4,2)},
                                                    {"Efficiency", EnchantInfo(5,1,1)},
                                                    {"Feather Falling", EnchantInfo(4,2,1)},
                                                    {"Fire Aspect", EnchantInfo(2,4,2)},
                                                    {"Fire Protection", EnchantInfo(4,2,1)},
                                                    {"Flame", EnchantInfo(1,4,2)},
                                                    {"Fortune", EnchantInfo(3,4,2)},
                                                    {"Impaling", EnchantInfo(5,4,2)},
                                                    {"Knockback", EnchantInfo(2,2,1)},
                                                    {"Looting", EnchantInfo(3,4,2)},
                                                    {"Loyalty", EnchantInfo(3,2,1)},
                                                    {"Luck of the Sea", EnchantInfo(3,4,2)},
                                                    {"Lure", EnchantInfo(3,4,2)},
                                                    {"Mending", EnchantInfo(1,4,2)},
                                                    {"Multishot", EnchantInfo(1,4,2)},
                                                    {"Piercing", EnchantInfo(4,1,1)},
                                                    {"Power", EnchantInfo(5,1,1)},
                                                    {"Projectile Protection", EnchantInfo(4,2,1)},
                                                    {"Protection", EnchantInfo(4,1,1)},
                                                    {"Punch", EnchantInfo(2,4,2)},
                                                    {"Quick Charge", EnchantInfo(3,2,1)},
                                                    {"Respiration", EnchantInfo(3,4,2)},
                                                    {"Riptide", EnchantInfo(3,4,2)},
                                                    {"Sharpness", EnchantInfo(5,1,1)},
                                                    {"Silk Touch", EnchantInfo(1,8,4)},
                                                    {"Smite", EnchantInfo(5,2,1)},
                                                    {"Soul Speed", EnchantInfo(3,8,4)},
                                                    {"Sweeping Edge", EnchantInfo(3,4,2)},
                                                    {"Thorns", EnchantInfo(3,8,4)},
                                                    {"Unbreaking", EnchantInfo(3,2,1)} };*/
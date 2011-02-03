/* Copyright (C) 2006 - 2011 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: assembly_of_iron
SD%Complete: 0%
SDComment: 
SDCategory: Ulduar
EndScriptData */

#include "precompiled.h"
#include "ulduar.h"

enum
{
    SAY_BRUNDIR_AGGRO                   = -1603056,
    SAY_BRUNDIR_WHIRL                   = -1603057,
    SAY_BRUNDIR_DEATH_1                 = -1603058,
    SAY_BRUNDIR_DEATH_2                 = -1603059,
    SAY_BRUNDIR_SLAY_1                  = -1603060,
    SAY_BRUNDIR_SLAY_2                  = -1603061,
    SAY_BRUNDIR_BERSERK                 = -1603062,
    SAY_BRUNDIR_FLY                     = -1603063,

    SAY_MOLGEIM_AGGRO                   = -1603064,
    SAY_MOLGEIM_DEATH_1                 = -1603065,
    SAY_MOLGEIM_DEATH_2                 = -1603066,
    SAY_MOLGEIM_DEATH_RUNE              = -1603067,
    SAY_MOLGEIM_SURGE                   = -1603068,
    SAY_MOLGEIM_SLAY_1                  = -1603069,
    SAY_MOLGEIM_SLAY_2                  = -1603070,
    SAY_MOLGEIM_BERSERK                 = -1603071,

    SAY_STEEL_AGGRO                     = -1603072,
    SAY_STEEL_DEATH_1                   = -1603073,
    SAY_STEEL_DEATH_2                   = -1603074,
    SAY_STEEL_SLAY_1                    = -1603075,
    SAY_STEEL_SLAY_2                    = -1603076,
    SAY_STEEL_OVERWHELM                 = -1603077,
    SAY_STEEL_BERSERK                   = -1603078,

    //all
    SPELL_BERSERK                       = 47008,
    SPELL_SUPERCHARGE                   = 61920,
    NPC_WORLD_TRIGGER                   = 22515,
    //steelbreaker
    SPELL_HIGH_VOLTAGE                  = 61890,
    SPELL_HIGH_VOLTAGE_H                = 63498,
    SPELL_FUSION_PUNCH                  = 61903,
    SPELL_FUSION_PUNCH_H                = 63493,
    SPELL_STATIC_DISRUPTION             = 44008,
    SPELL_STATIC_DISRUPTION_H           = 63494,
    SPELL_POWER                         = 64637,
    SPELL_POWER_H                       = 61888,
    SPELL_ELECTRICAL_CHARGE             = 61902,
    //runemaster molgeim
    SPELL_SHIELD                        = 62274,
    SPELL_SHIELD_H                      = 63489,
    SPELL_RUNE_OF_POWER                 = 63513,
    SPELL_RUNE_OF_DEATH                 = 62269,
    SPELL_RUNE_OF_DEATH_H               = 63490,
    SPELL_RUNE_OF_SUMMONING             = 62273,
    //rune of power
    AURA_RUNE_OF_POWER                  = 61974,
    //rune of summoning
    AURA_RUNE_OF_SUMMONING              = 62019,
    //lightning elemental
    SPELL_LIGHTNING_BLAST               = 62054,
    SPELL_LIGHTNING_BLAST_H             = 63491,
    //stormcaller brundir
    SPELL_CHAIN_LIGHTNING               = 61879,
    SPELL_CHAIN_LIGHTNING_H             = 63479,
    SPELL_OVERLOAD                      = 61869,
    SPELL_LIGHTNING_WHIRL               = 61915,
    SPELL_LIGHTNING_WHIRL_H             = 63483,
    SPELL_STORMSHIELD                   = 64187,
    SPELL_LIGHTNING_TENDRILS            = 61887,
    SPELL_LIGHTNING_TENDRILS_H          = 63486,
    LIGHTNING_TENDRILS_VISUAL           = 61883,

    NPC_LIGHTNING_ELEMENTAL             = 32958,

    ACHIEV_ON_YOUR_SIDE                 = 2945,
    ACHIEV_ON_YOUR_SIDE_H               = 2946,
    SPELL_IRON_BOOT_AURA                = 58501,

    ACHIEV_CHOOSE_BRUNDIR               = 2940,
    ACHIEV_CHOOSE_BRUNDIR_H             = 2943,
    ACHIEV_CHOOSE_MOLGEIM               = 2939,
    ACHIEV_CHOOSE_MOLGEIM_H             = 2942,
    ACHIEV_CHOOSE_STEELBREAKER          = 2941,
    ACHIEV_CHOOSE_STEELBREAKER_H        = 2944,
};

// Rune of Power
struct MANGOS_DLL_DECL mob_rune_of_powerAI : public ScriptedAI
{
    mob_rune_of_powerAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        SetCombatMovement(false);
        Reset();
    }

    uint32 m_uiDeath_Timer;

    void Reset()
    {
        m_uiDeath_Timer = 60000;
        m_creature->setFaction(35);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        DoCast(m_creature,  AURA_RUNE_OF_POWER);
    }

    void UpdateAI(const uint32 diff)
    {
        if (m_uiDeath_Timer < diff)
        {
            m_creature->DealDamage(m_creature, m_creature->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
        }
        else m_uiDeath_Timer -= diff;
    }
};

CreatureAI* GetAI_mob_rune_of_power(Creature* pCreature)
{
    return new mob_rune_of_powerAI(pCreature);
}

// Lightning Elemental
struct MANGOS_DLL_DECL mob_ulduar_lightning_elementalAI : public ScriptedAI
{
    mob_ulduar_lightning_elementalAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiDeath_Timer;
    uint32 m_uiCheck_Timer;
    bool m_bWillExplode;

    void Reset()
    {
        m_bWillExplode  = false;
        m_uiCheck_Timer = 1000;
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiDeath_Timer < diff && m_bWillExplode)
        {
            m_creature->DealDamage(m_creature, m_creature->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
        }
        else m_uiDeath_Timer -= diff;

        if (m_uiCheck_Timer < diff)
        {
            if (m_creature->IsWithinDistInMap(m_creature->getVictim(), 15.0f))
            {
                DoCast(m_creature, m_bIsRegularMode ? SPELL_LIGHTNING_BLAST : SPELL_LIGHTNING_BLAST_H);
                m_bWillExplode  = true;
                m_uiDeath_Timer = 500;
                m_uiCheck_Timer = 5000;
            }
            m_uiCheck_Timer = 1000;
        }
        else m_uiCheck_Timer -= diff;
    }
};

CreatureAI* GetAI_mob_ulduar_lightning_elemental(Creature* pCreature)
{
    return new mob_ulduar_lightning_elementalAI(pCreature);
}

// Rune of Summoning
struct MANGOS_DLL_DECL mob_rune_of_summoningAI : public ScriptedAI
{
    mob_rune_of_summoningAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        SetCombatMovement(false);
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiDeath_Timer;
    uint32 m_uiSummon_Timer;
    uint32 m_uiSummonNum;

    void Reset()
    {
        m_uiDeath_Timer     = 0;
        m_uiSummon_Timer    = 5000;
        m_creature->setFaction(35);
        m_creature->SetInCombatWithZone();
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        DoCast(m_creature,  AURA_RUNE_OF_SUMMONING, true);

        if (m_pInstance)
            m_uiSummonNum = m_pInstance->instance->GetPlayersCountExceptGMs();
    }

    void JustSummoned(Creature* pSummoned)
    {
        pSummoned->SetInCombatWithZone();
        if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            pSummoned->AddThreat(pTarget, 100.0f);
    }

    void UpdateAI(const uint32 diff)
    {
        if (m_uiSummon_Timer < diff)
        {
            if (Creature* pTemp = m_creature->SummonCreature(NPC_LIGHTNING_ELEMENTAL, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000))
                m_uiSummonNum--;

            if (m_uiSummonNum == 0)
                m_creature->DealDamage(m_creature, m_creature->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);

            m_uiSummon_Timer = 500;
        } else m_uiSummon_Timer -= diff;
    }
};

CreatureAI* GetAI_mob_rune_of_summoning(Creature* pCreature)
{
    return new mob_rune_of_summoningAI(pCreature);
}

//Stormcaller Brundir
struct MANGOS_DLL_DECL boss_brundirAI : public ScriptedAI
{
    boss_brundirAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiChain_Lightning_Timer;
    uint32 m_uiOverload_Timer;
    uint32 m_uiWhirl_Timer;
    uint32 m_uiTendrils_start_Timer;
    uint32 m_uiTendrils_Change;
    uint32 m_uiTendrils_end_Timer;
    uint32 m_uiDie_delay;
    uint32 m_uiEnrage_Timer;
    uint32 m_uiCheckTimer;

    bool m_bHasSupercharge1;
    bool m_bHasSupercharge2;
    bool m_bIsTendrils;
    bool m_bMustDie;
    bool m_bIsSteelbreakerDead;
    bool m_bIsMolgeimDead;
    bool m_bIsEnrage;

    void Reset()
    {
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
        m_uiChain_Lightning_Timer = 0;
        m_uiOverload_Timer      = 35000;
        m_uiEnrage_Timer        = 900000;
        m_uiCheckTimer          = 1000;
        m_bIsEnrage             = false;
        m_bHasSupercharge1      = false;
        m_bHasSupercharge2      = false;
        m_bIsTendrils           = false;
        m_bIsSteelbreakerDead   = false;
        m_bIsMolgeimDead        = false;
        m_bMustDie              = false;
        if (m_creature->HasAura(SPELL_SUPERCHARGE))
            m_creature->RemoveAurasDueToSpell(SPELL_SUPERCHARGE);
    }

    void DamageTaken(Unit* pDoneBy, uint32& uiDamage)
    {
        if (uiDamage > m_creature->GetHealth() && !m_bMustDie)
        {
            uiDamage = 0;
            m_creature->CastStop();
            m_creature->RemoveAllAuras();
            // stacking workaround
            if (Creature *pTrigger = GetClosestCreatureWithEntry(m_creature, NPC_WORLD_TRIGGER, 100.0f))
                m_creature->CastSpell(m_creature, SPELL_SUPERCHARGE, true, 0, 0, pTrigger->GetObjectGuid());
            else
                DoCast(m_creature, SPELL_SUPERCHARGE, true);
            m_uiDie_delay   = 500;
            m_bMustDie      = true;
        }
    }

    void JustDied(Unit* pKiller)
    {
        m_creature->RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE);
        // if all of them are dead
        if (m_pInstance)
        {
            // remove supercharge from players -> spell bug
            //m_pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_SUPERCHARGE);
            // if the others are dead then give loot
            if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_STEELBREAKER)))
            {
                if (!pTemp->isAlive())
                {
                    if (Creature* p2Temp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_MOLGEIM)))
                    {
                        if (!p2Temp->isAlive())
                        {
                            m_pInstance->SetData(TYPE_ASSEMBLY, DONE);
                            // only the current one has loot, because loot modes are implemented in sql
                            m_creature->SetFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE);
                        }
                    }
                }
            }

            // else make them full hp
            if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_STEELBREAKER)))
            {
                if (pTemp->isAlive())
                    pTemp->SetHealth(pTemp->GetMaxHealth());
            }
            if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_MOLGEIM)))
            {
                if (pTemp->isAlive())
                    pTemp->SetHealth(pTemp->GetMaxHealth());
            }
        }

        if(irand(0,1))
            DoScriptText(SAY_BRUNDIR_DEATH_1, m_creature);
        else
            DoScriptText(SAY_BRUNDIR_DEATH_2, m_creature);
    }

    void Aggro(Unit* pWho)
    {
        bool bCanSayAggro = true;

        if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_STEELBREAKER)))
        {
            if (pTemp->isInCombat())
                bCanSayAggro = false;
            else if (pTemp->isAlive())
                pTemp->SetInCombatWithZone();
        }
        if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_MOLGEIM)))
        {
            if (pTemp->isInCombat())
                bCanSayAggro = false;
            else if (pTemp->isAlive())
                pTemp->SetInCombatWithZone();
        }
        if (m_pInstance)
        {
            if(m_pInstance->GetData(TYPE_ASSEMBLY) != IN_PROGRESS)
                m_pInstance->SetData(TYPE_ASSEMBLY, IN_PROGRESS);
        }

        if (bCanSayAggro)
            DoScriptText(SAY_BRUNDIR_AGGRO, m_creature);
    }

    void JustReachedHome()
    {
        if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_STEELBREAKER)))
        {
            if (!pTemp->isAlive())
                pTemp->Respawn();
        }
        if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_MOLGEIM)))
        {
            if (!pTemp->isAlive())
                pTemp->Respawn();
        }
        if (m_pInstance)
        {
            if(m_pInstance->GetData(TYPE_ASSEMBLY) != FAIL)
                m_pInstance->SetData(TYPE_ASSEMBLY, FAIL);
        }
    }

    void KilledUnit(Unit* pWho)
    {
        DoScriptText(urand(0, 1) ? SAY_BRUNDIR_SLAY_1 : SAY_BRUNDIR_SLAY_2, m_creature);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // level 1 spells
        if (m_uiChain_Lightning_Timer < uiDiff && !m_bIsTendrils)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                if (DoCastSpellIfCan(pTarget, m_bIsRegularMode ? SPELL_CHAIN_LIGHTNING : SPELL_CHAIN_LIGHTNING_H) == CAST_OK)
                {
                    if (roll_chance_i(30))
                    {
                        m_uiChain_Lightning_Timer = 5000;
                        SetCombatMovement(true);
                    }
                    else
                    {
                        m_uiChain_Lightning_Timer = 2100;
                        SetCombatMovement(false);
                    }
                }
        }
        else m_uiChain_Lightning_Timer -= uiDiff;

        if (m_uiOverload_Timer < uiDiff && !m_bIsTendrils)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_OVERLOAD) == CAST_OK)
                m_uiOverload_Timer = 40000;
        }
        else m_uiOverload_Timer -= uiDiff;

        // level 2 spells
        if (m_uiWhirl_Timer < uiDiff && !m_bIsTendrils && m_bHasSupercharge1)
        {
            // wait until Overload is cast
            if (m_creature->GetCurrentSpell(CURRENT_CHANNELED_SPELL))
                m_uiWhirl_Timer = 1000;
            else
            {
                m_creature->CastStop();
                DoScriptText(SAY_BRUNDIR_WHIRL, m_creature);
                DoCast(m_creature, m_bIsRegularMode ? SPELL_LIGHTNING_WHIRL : SPELL_LIGHTNING_WHIRL_H);
                m_uiWhirl_Timer = 15000;
            }
        }
        else m_uiWhirl_Timer -= uiDiff;

        // level 3 spells
        // boss doesn't fly during tendrils, needs fixing!
        if (m_uiTendrils_start_Timer < uiDiff && m_bHasSupercharge2)
        {
            if (!m_bIsTendrils)
            {
                m_creature->CastStop();
                SetCombatMovement(false);
                DoCast(m_creature, LIGHTNING_TENDRILS_VISUAL);
                DoScriptText(SAY_BRUNDIR_FLY, m_creature);
                m_bIsTendrils = true;
                m_creature->SetSpeedRate(MOVE_RUN, 0.8f);
                m_uiTendrils_start_Timer = 3000;
                m_uiTendrils_end_Timer = 30000;
                m_uiTendrils_Change = 5000;
            }
            else
            {
                SetCombatMovement(true);
                if (DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_LIGHTNING_TENDRILS : SPELL_LIGHTNING_TENDRILS_H) == CAST_OK)
                    m_uiTendrils_start_Timer = 90000;
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                    m_creature->AI()->AttackStart(pTarget);
            }
        }
        else m_uiTendrils_start_Timer -= uiDiff;

        if (m_bIsTendrils)
        {
            if (m_uiTendrils_Change < uiDiff)
            {
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                {
                    DoResetThreat();
                    m_creature->AI()->AttackStart(pTarget);
                    m_uiTendrils_Change = 6000;
                }
            }
            else m_uiTendrils_Change -= uiDiff;
        }

        if (m_uiTendrils_end_Timer < uiDiff && m_bIsTendrils)
        {
            if (m_creature->HasAura(SPELL_LIGHTNING_TENDRILS))
                m_creature->RemoveAurasDueToSpell(SPELL_LIGHTNING_TENDRILS);
            if (m_creature->HasAura(SPELL_LIGHTNING_TENDRILS_H))
                m_creature->RemoveAurasDueToSpell(SPELL_LIGHTNING_TENDRILS_H);
            if (m_creature->HasAura(LIGHTNING_TENDRILS_VISUAL))
                m_creature->RemoveAurasDueToSpell(LIGHTNING_TENDRILS_VISUAL);
            m_uiTendrils_start_Timer = 90000;
            m_creature->SetSpeedRate(MOVE_RUN, 1.8f);
            m_bIsTendrils = false;
            m_uiChain_Lightning_Timer = 5000;
            m_uiOverload_Timer = 35000;
            m_uiWhirl_Timer = 10000;
        }
        else m_uiTendrils_end_Timer -= uiDiff;

        // die after casting supercharge
        if (m_uiDie_delay < uiDiff && m_bMustDie)
            m_creature->DealDamage(m_creature, m_creature->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
        else m_uiDie_delay -= uiDiff;

        if (m_uiEnrage_Timer < uiDiff && !m_bIsEnrage)
        {
            DoScriptText(SAY_BRUNDIR_BERSERK, m_creature);
            if (DoCastSpellIfCan(m_creature, SPELL_BERSERK) == CAST_OK)
                m_bIsEnrage = true;
        }
        else m_uiEnrage_Timer -= uiDiff;

        // check if the others are dead
        if (m_uiCheckTimer < uiDiff && !m_bHasSupercharge2)
        {
            if (!m_bIsSteelbreakerDead)
            {
                if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_STEELBREAKER)))
                {
                    if (!pTemp->isAlive())
                    {
                        m_bIsSteelbreakerDead = true;
                        if (!m_bHasSupercharge1)
                        {
                            m_bHasSupercharge1 = true;
                            m_uiWhirl_Timer = 10000;
                        }
                        else
                        {
                            m_bHasSupercharge2 = true;
                            m_uiTendrils_start_Timer = 40000;
                            m_uiTendrils_end_Timer = 60000;
                            m_uiTendrils_Change = 6000;
                        }
                    }
                }
            }
            if (!m_bIsMolgeimDead)
            {
                if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_MOLGEIM)))
                {
                    if (!pTemp->isAlive())
                    {
                        m_bIsMolgeimDead = true;
                        if (!m_bHasSupercharge1)
                        {
                            m_bHasSupercharge1 = true;
                            m_uiWhirl_Timer = 10000;
                        }
                        else
                        {
                            m_bHasSupercharge2 = true;
                            m_uiTendrils_start_Timer = 40000;
                            m_uiTendrils_end_Timer = 60000;
                            m_uiTendrils_Change = 6000;
                        }
                    }
                }
            }
            m_uiCheckTimer = 1000;
        }
        else m_uiCheckTimer -= uiDiff;

        if (!m_bIsTendrils && !m_bMustDie)
            DoMeleeAttackIfReady();
    }
 };
 
CreatureAI* GetAI_boss_brundir(Creature* pCreature)
{
    return new boss_brundirAI(pCreature);
}

//Runemaster Molgeim
struct MANGOS_DLL_DECL boss_molgeimAI : public ScriptedAI
{
    boss_molgeimAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiShield_Timer;
    uint32 m_uiRune_Power_Timer;
    uint32 m_uiRune_Death_Timer;
    uint32 m_uiRune_Summon_Timer;
    uint32 m_uiDie_delay;
    uint32 m_uiEnrage_Timer;
    uint32 m_uiCheckTimer;

    bool m_bSupercharge1;
    bool m_bSupercharge2;
    bool m_bMustDie;
    bool m_bBrundirDead;
    bool m_bSteelbreakerDead;
    bool m_bEnrage;

    void Reset()
    {
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
        m_uiShield_Timer    = 20000;
        m_uiRune_Power_Timer = 10000;
        m_uiEnrage_Timer    = 900000;
        m_uiCheckTimer      = 1000;
        m_bEnrage           = false;
        m_bBrundirDead      = false;
        m_bSteelbreakerDead = false;
        m_bSupercharge1     = false;
        m_bSupercharge2     = false;
        m_bMustDie          = false;
        if (m_creature->HasAura(SPELL_SUPERCHARGE))
            m_creature->RemoveAurasDueToSpell(SPELL_SUPERCHARGE);
    }

    void DamageTaken(Unit* pDoneBy, uint32& uiDamage)
    {
        if (uiDamage > m_creature->GetHealth() && !m_bMustDie)
        {
            uiDamage = 0;
            m_creature->RemoveAllAuras();
            m_creature->CastStop();
            // stacking workaround
            if (Creature *pTrigger = GetClosestCreatureWithEntry(m_creature, NPC_WORLD_TRIGGER, 100.0f))
                m_creature->CastSpell(m_creature, SPELL_SUPERCHARGE, true, 0, 0, pTrigger->GetObjectGuid());
            else
                DoCast(m_creature, SPELL_SUPERCHARGE, true);
            m_uiDie_delay = 500;
            m_bMustDie = true;
        }
    }

    void JustDied(Unit* pKiller)
    {
        //death yell
        m_creature->RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE);
        if (m_pInstance)
        {
            // remove supercharge from players -> spell bug
            //m_pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_SUPERCHARGE);
            // if the others are dead then give loot
            if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_STEELBREAKER)))
            {
                if (!pTemp->isAlive())
                {
                    if (Creature* p2Temp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_BRUNDIR)))
                    {
                        if (!p2Temp->isAlive())
                        {
                            m_pInstance->SetData(TYPE_ASSEMBLY, DONE);
                            // only the current one has loot, because loot modes are implemented in sql
                            m_creature->SetFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE);
                        }
                    }
                }
            }

            // else make them full hp
            if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_STEELBREAKER)))
            {
                if (pTemp->isAlive())
                    pTemp->SetHealth(pTemp->GetMaxHealth());
            }
            if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_BRUNDIR)))
            {
                if (pTemp->isAlive())
                    pTemp->SetHealth(pTemp->GetMaxHealth());
            }
        }

        DoScriptText(urand(0, 1) ? SAY_MOLGEIM_DEATH_1 : SAY_MOLGEIM_DEATH_2, m_creature);
    }

    void Aggro(Unit* pWho)
    {
        bool bCanSayAggro = true;

        if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_STEELBREAKER)))
        {
            if (pTemp->isInCombat())
                bCanSayAggro = false;
            else if (pTemp->isAlive())
                pTemp->SetInCombatWithZone();
        }
        if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_BRUNDIR)))
        {
            if (pTemp->isInCombat())
                bCanSayAggro = false;
            else if (pTemp->isAlive())
                pTemp->SetInCombatWithZone();
        }
        if (m_pInstance)
        {
            if(m_pInstance->GetData(TYPE_ASSEMBLY) != IN_PROGRESS)
                m_pInstance->SetData(TYPE_ASSEMBLY, IN_PROGRESS);
        }

        if (bCanSayAggro)
            DoScriptText(SAY_MOLGEIM_AGGRO, m_creature);
    }

    void JustReachedHome()
    {
        if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_STEELBREAKER)))
        {
            if (!pTemp->isAlive())
                pTemp->Respawn();
        }
        if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_BRUNDIR)))
        {
            if (!pTemp->isAlive())
                pTemp->Respawn();
        }
        if (m_pInstance)
        {
            if(m_pInstance->GetData(TYPE_ASSEMBLY) != FAIL)
                m_pInstance->SetData(TYPE_ASSEMBLY, FAIL);
        }
    }

    void KilledUnit(Unit* pWho)
    {
        DoScriptText(urand(0, 1) ? SAY_MOLGEIM_SLAY_1 : SAY_MOLGEIM_SLAY_2, m_creature);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // level 1 spells
        if (m_uiShield_Timer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_SHIELD : SPELL_SHIELD_H) == CAST_OK)
                m_uiShield_Timer = 50000;
        }
        else m_uiShield_Timer -= uiDiff;

        if (m_uiRune_Power_Timer < uiDiff)
        {
            switch(urand(0, 2))
            {
            case 0:
                if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_BRUNDIR)))
                {
                    if (pTemp->isAlive())
                        DoCast(pTemp, SPELL_RUNE_OF_POWER);
                    else
                        DoCast(m_creature, SPELL_RUNE_OF_POWER);
                }
                break;
            case 1:
                if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_STEELBREAKER)))
                {
                    if (pTemp->isAlive())
                        DoCast(pTemp, SPELL_RUNE_OF_POWER);
                    else
                        DoCast(m_creature, SPELL_RUNE_OF_POWER);
                }
                break;
            case 2:
                DoCast(m_creature, SPELL_RUNE_OF_POWER);
                break;
            }
            m_uiRune_Power_Timer = 30000;
        }
        else m_uiRune_Power_Timer -= uiDiff;

        // level2 spells
        if (m_uiRune_Death_Timer < uiDiff && m_bSupercharge1)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (DoCastSpellIfCan(pTarget, m_bIsRegularMode ? SPELL_RUNE_OF_DEATH : SPELL_RUNE_OF_DEATH_H) == CAST_OK)
                {
                    m_uiRune_Death_Timer = 30000;
                    DoScriptText(SAY_MOLGEIM_DEATH_RUNE, m_creature);
                }
            }
        }
        else m_uiRune_Death_Timer -= uiDiff;

        // level 3 spells
        if (m_uiRune_Summon_Timer < uiDiff && m_bSupercharge2)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                DoCast(pTarget, SPELL_RUNE_OF_SUMMONING);
                m_uiRune_Summon_Timer = 30000;
                DoScriptText(SAY_MOLGEIM_SURGE, m_creature);
            }
        }
        else m_uiRune_Summon_Timer -= uiDiff;

        // die after overloading
        if (m_uiDie_delay < uiDiff && m_bMustDie)
        {
            m_creature->DealDamage(m_creature, m_creature->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
        }
        else m_uiDie_delay -= uiDiff;

        if (m_uiEnrage_Timer < uiDiff && !m_bEnrage)
        {
            DoScriptText(SAY_MOLGEIM_BERSERK, m_creature);
            if (DoCastSpellIfCan(m_creature, SPELL_BERSERK) == CAST_OK)
                m_bEnrage = true;
        }
        else m_uiEnrage_Timer -= uiDiff;

        if (m_uiCheckTimer < uiDiff)
        {
            if (!m_bSteelbreakerDead)
            {
                if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_STEELBREAKER)))
                {
                    if (!pTemp->isAlive())
                    {
                        m_bSteelbreakerDead = true;
                        if (!m_bSupercharge1)
                        {
                            m_bSupercharge1 = true;
                            m_uiRune_Death_Timer = 10000;
                        }
                        else
                        {
                            m_bSupercharge2 = true;
                            m_uiRune_Summon_Timer = 20000;
                        }
                    }
                }
            }
            if (!m_bBrundirDead)
            {
                if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_BRUNDIR)))
                {
                    if (!pTemp->isAlive())
                    {
                        m_bBrundirDead = true;
                        if (!m_bSupercharge1)
                        {
                            m_bSupercharge1 = true;
                            m_uiRune_Death_Timer = 10000;
                        }
                        else
                        {
                            m_bSupercharge2 = true;
                            m_uiRune_Summon_Timer = 20000;
                        }
                    }
                }
            }
            m_uiCheckTimer = 1000;
        }
        else m_uiCheckTimer -= uiDiff;

        if (!m_bMustDie)
            DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_molgeim(Creature* pCreature)
{
    return new boss_molgeimAI(pCreature);
}

//Steelbreaker
struct MANGOS_DLL_DECL boss_steelbreakerAI : public ScriptedAI
{
    boss_steelbreakerAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiFusion_Punch_Timer;
    uint32 m_uiStatic_Disruption_Timer;
    uint32 m_uiPower_Timer;
    uint32 m_uiDie_delay;
    uint32 m_uiEnrage_Timer;
    uint32 m_uiCheckTimer;

    bool m_bBrundirDead;
    bool m_bMolgeimDead;
    bool m_bSupercharge1;
    bool m_bSupercharge2;
    bool m_bMustDie;
    bool m_bEnrage;

    void Reset()
    {
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
        m_uiFusion_Punch_Timer = 20000;
        m_uiEnrage_Timer    = 900000;
        m_uiCheckTimer      = 1000;
        m_bEnrage           = false;
        m_bBrundirDead      = false;
        m_bMolgeimDead      = false;
        m_bSupercharge1     = false;
        m_bSupercharge2     = false;
        m_bMustDie          = false;
        if (m_creature->HasAura(SPELL_SUPERCHARGE))
            m_creature->RemoveAurasDueToSpell(SPELL_SUPERCHARGE);
        if (m_creature->HasAura(SPELL_ELECTRICAL_CHARGE))
            m_creature->RemoveAurasDueToSpell(SPELL_ELECTRICAL_CHARGE);
        if (m_creature->HasAura(SPELL_HIGH_VOLTAGE))
            m_creature->RemoveAurasDueToSpell(SPELL_HIGH_VOLTAGE);
        if (m_creature->HasAura(SPELL_HIGH_VOLTAGE_H))
            m_creature->RemoveAurasDueToSpell(SPELL_HIGH_VOLTAGE_H);
    }

    void KilledUnit(Unit* pVictim)
    {
        if (m_bSupercharge2)
            DoCast(m_creature, SPELL_ELECTRICAL_CHARGE, true);

        DoScriptText(urand(0, 1) ? SAY_STEEL_SLAY_1 : SAY_STEEL_SLAY_2, m_creature);
    }

    void DamageTaken(Unit* pDoneBy, uint32& uiDamage)
    {
        if (uiDamage > m_creature->GetHealth() && !m_bMustDie)
        {
            uiDamage = 0;
            m_creature->CastStop();
            m_creature->RemoveAllAuras();
            // stacking workaround
            if (Creature *pTrigger = GetClosestCreatureWithEntry(m_creature, NPC_WORLD_TRIGGER, 100.0f))
                m_creature->CastSpell(m_creature, SPELL_SUPERCHARGE, true, 0, 0, pTrigger->GetObjectGuid());
            else
                DoCast(m_creature, SPELL_SUPERCHARGE, true);
            m_uiDie_delay   = 500;
            m_bMustDie      = true;
        }
    }

    void OnYourSide()
    {
        /* hacky way to complete achievements; use only if you have this function
        Map* pMap = m_creature->GetMap();
        AchievementEntry const *AchievYourSide = GetAchievementStore()->LookupEntry(m_bIsRegularMode ? ACHIEV_ON_YOUR_SIDE : ACHIEV_ON_YOUR_SIDE_H);
        if(AchievYourSide && pMap)
        {
            Map::PlayerList const &lPlayers = pMap->GetPlayers();
            if (!lPlayers.isEmpty())
            {
                for(Map::PlayerList::const_iterator itr = lPlayers.begin(); itr != lPlayers.end(); ++itr)
                {
                    if (Player* pPlayer = itr->getSource())
                    {
                        if(pPlayer->HasAura(SPELL_IRON_BOOT_AURA, EFFECT_INDEX_0))
                            pPlayer->CompletedAchievement(AchievYourSide);
                    }
                }
            }
        }
        */
    }

    void JustDied(Unit* pKiller)
    {
        m_creature->RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE);
        if (m_pInstance)
        {
            // remove supercharge from players -> spell bug
           // m_pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_SUPERCHARGE);
            // if the others are dead then give loot
            if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_MOLGEIM)))
            {
                if (!pTemp->isAlive())
                {
                    if (Creature* p2Temp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_BRUNDIR)))
                    {
                        if (!p2Temp->isAlive())
                        {
                            m_pInstance->SetData(TYPE_ASSEMBLY, DONE);
                            m_pInstance->SetData(TYPE_ASSEMBLY_HARD, DONE);
                            // only the current one has loot, because loot modes are implemented in sql
                            m_creature->SetFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE);

                            // I'm on your side
                            OnYourSide();

                            // ChooseSteelbreaker
                            // hacky way to complete achievements; use only if you have this function
                            // m_pInstance->DoCompleteAchievement(m_bIsRegularMode ? ACHIEV_CHOOSE_STEELBREAKER : ACHIEV_CHOOSE_STEELBREAKER_H);
                            }
                    }
                }
            }

            // else make them full hp
            if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_BRUNDIR)))
            {
                if (pTemp->isAlive())
                    pTemp->SetHealth(pTemp->GetMaxHealth());
            }
            if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_MOLGEIM)))
            {
                if (pTemp->isAlive())
                    pTemp->SetHealth(pTemp->GetMaxHealth());
            }
        }

        DoScriptText(urand(0, 1) ? SAY_STEEL_DEATH_1 : SAY_STEEL_DEATH_2, m_creature);
    }

    void Aggro(Unit* pWho)
    {
        bool bCanSayAggro = true;

        if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_MOLGEIM)))
        {
            if (pTemp->isInCombat())
                bCanSayAggro = false;
            else if (pTemp->isAlive())
                pTemp->SetInCombatWithZone();
        }
        if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_BRUNDIR)))
        {
            if (pTemp->isInCombat())
                bCanSayAggro = false;
            else if (pTemp->isAlive())
                pTemp->SetInCombatWithZone();
        }

        DoCast(m_creature, m_bIsRegularMode ? SPELL_HIGH_VOLTAGE : SPELL_HIGH_VOLTAGE_H, true);

        if (m_pInstance)
        {
            if(m_pInstance->GetData(TYPE_ASSEMBLY) != IN_PROGRESS)
                m_pInstance->SetData(TYPE_ASSEMBLY, IN_PROGRESS);
        }

        if (bCanSayAggro)
            DoScriptText(SAY_STEEL_AGGRO, m_creature);
    }

    void JustReachedHome()
    {
        if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_MOLGEIM)))
        {
            if (!pTemp->isAlive())
                pTemp->Respawn();
        }
        if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_BRUNDIR)))
        {
            if (!pTemp->isAlive())
                pTemp->Respawn();
        }
        if (m_pInstance)
        {
            if(m_pInstance->GetData(TYPE_ASSEMBLY) != FAIL)
                m_pInstance->SetData(TYPE_ASSEMBLY, FAIL);
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // level 1 spells
        if (m_uiFusion_Punch_Timer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), m_bIsRegularMode ? SPELL_FUSION_PUNCH : SPELL_FUSION_PUNCH_H) == CAST_OK)
                m_uiFusion_Punch_Timer = 20000;
        }else m_uiFusion_Punch_Timer -= uiDiff;

        // level 2 spells
        if (m_uiStatic_Disruption_Timer < uiDiff && m_bSupercharge1)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
                if (DoCastSpellIfCan(pTarget, m_bIsRegularMode ? SPELL_STATIC_DISRUPTION : SPELL_STATIC_DISRUPTION_H) == CAST_OK)
                    m_uiStatic_Disruption_Timer = 60000;
        }
        else m_uiStatic_Disruption_Timer -= uiDiff;

        // level 3 spells
        if (m_uiPower_Timer < uiDiff && m_bSupercharge2)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_TOPAGGRO, 0))
            {
                if (DoCastSpellIfCan(pTarget, m_bIsRegularMode ? SPELL_POWER : SPELL_POWER_H) == CAST_OK)
                {
                    DoScriptText(SAY_STEEL_OVERWHELM, m_creature);
                    m_uiPower_Timer = m_bIsRegularMode ? 65000 : 35000;
                }
            }
        }
        else m_uiPower_Timer -= uiDiff;

        if (m_uiDie_delay < uiDiff && m_bMustDie)
        {
            m_creature->DealDamage(m_creature, m_creature->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
        }
        else m_uiDie_delay -= uiDiff;

        if (m_uiEnrage_Timer < uiDiff && !m_bEnrage)
        {
            DoScriptText(SAY_STEEL_BERSERK, m_creature);
            if (DoCastSpellIfCan(m_creature, SPELL_BERSERK) == CAST_OK)
                m_bEnrage = true;
        }
        else m_uiEnrage_Timer -= uiDiff;

        if (m_uiCheckTimer < uiDiff)
        {
            if (!m_bBrundirDead)
            {
                if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_BRUNDIR)))
                {
                    if (!pTemp->isAlive())
                    {
                        m_bBrundirDead = true;
                        if (!m_bSupercharge1)
                        {
                            m_bSupercharge1 = true;
                            m_uiStatic_Disruption_Timer = 12000;
                        }
                        else
                        {
                            m_bSupercharge2 = true;
                            m_uiPower_Timer = 5000;
                        }
                    }
                }
            }
            if (!m_bMolgeimDead)
            {
                if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_MOLGEIM)))
                {
                    if (!pTemp->isAlive())
                    {
                        m_bMolgeimDead = true;
                        if (!m_bSupercharge1)
                        {
                            m_bSupercharge1 = true;
                            m_uiStatic_Disruption_Timer = 22000;
                        }
                        else
                        {
                            m_bSupercharge2 = true;
                            m_uiPower_Timer = 5000;
                        }
                    }
                }
            }
            m_uiCheckTimer = 1000;
        }
        else m_uiCheckTimer -= uiDiff;

        if (!m_bMustDie)
            DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_steelbreaker(Creature* pCreature)
{
    return new boss_steelbreakerAI(pCreature);
}



void AddSC_boss_assembly_of_iron()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_brundir";
    pNewScript->GetAI = GetAI_boss_brundir;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_molgeim";
    pNewScript->GetAI = GetAI_boss_molgeim;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_steelbreaker";
    pNewScript->GetAI = GetAI_boss_steelbreaker;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_rune_of_power";
    pNewScript->GetAI = &GetAI_mob_rune_of_power;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_rune_of_summoning";
    pNewScript->GetAI = &GetAI_mob_rune_of_summoning;
    pNewScript->RegisterSelf();
 
    pNewScript = new Script;
    pNewScript->Name = "mob_ulduar_lightning_elemental";
    pNewScript->GetAI = &GetAI_mob_ulduar_lightning_elemental;
    pNewScript->RegisterSelf();
}

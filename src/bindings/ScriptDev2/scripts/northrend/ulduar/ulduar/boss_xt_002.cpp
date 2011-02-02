/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: boss_xt002
SD%Complete:
SDComment: need core support for light and gravity bomb. correct number of adds in 25man missing
SDCategory: Ulduar
EndScriptData */

#include "precompiled.h"
#include "ulduar.h"

enum
{
    //xt yells
    SAY_AGGRO               = -1610030,
    SAY_HEART_OPEN			= -1610031,
    SAY_HEART_CLOSE	        = -1610032,
    SAY_TANTRUM	            = -1610033,
    SAY_SLAY_01				= -1610034,
    SAY_SLAY_02				= -1610035,
    SAY_BERSERK				= -1610036,
    SAY_DEATH               = -1610037,
    SAY_ADDS				= -1610038,
    EMOTE_HEART             = -1610039,
    EMOTE_REPAIR            = -1610040,

    //xt-002
    SPELL_TANTRUM           = 62776,
    SPELL_LIGHT_BOMB_TRIG   = 65598,
    SPELL_LIGHT_BOMB		= 63018,
    SPELL_LIGHT_BOMB_H		= 65121,
    SPELL_GRAVITY_BOMB		= 63024,
    SPELL_GRAVITY_BOMB_H	= 64234,
    SPELL_ENRAGE			= 47008,
    SPELL_STUN				= 3618,
    SPELL_ENERGY_ORB        = 62790,

    // hard mode
    SPELL_HEARTBREAK        = 65737,
    SPELL_HEARTBREAK_H      = 64193,
    SPELL_VOIDZONE          = 64203,
    SPELL_VOIDZONE_H        = 64235,
    SPELL_VOIDZONE_EFFECT   = 46264,
    SPELL_LIFE_SPARK        = 64210,
    SPELL_SHOCK             = 64230,
    SPELL_STATIC_CHARGED    = 64227,

    NPC_VOIDZONE            = 34001,
    NPC_LIFESPARK           = 34004,

    //heart of the deconstructor
    SPELL_EXPOSED_HEART		= 63849,

    //XE-321 Boombot
    SPELL_BOOM				= 62834,

    //XM-024 Pummeller
    SPELL_CLEAVE			= 8374,
    SPELL_TRAMPLE			= 5568,
    SPELL_UPPERCUT			= 10966,

    // ScrapBot
    SPELL_SCRAP_REPAIR      = 62832,

    //NPC ids
    NPC_HEART				= 33329,
    NPC_SCRAPBOT			= 33343,
    NPC_BOOMBOT				= 33346,
    NPC_PUMMELER			= 33344, 

    // Achievs
    ACHIEV_HEARTBREAKER         = 3058,
    ACHIEV_HEARTBREAKER_H       = 3059,
    ACHIEV_DECONSTRUCT_FAST     = 2937,
    ACHIEV_DECONSTRUCT_FAST_H   = 2938,
    ACHIEV_NERF_ENGINEERING     = 2931,
    ACHIEV_NERF_ENGINEERING_H   = 2932,
    ACHIEV_NERF_GRAVITY_BOMBS   = 2934,
    ACHIEV_NERF_GRAVITY_BOMBS_H = 2936,
    ACHIEV_NERF_SCRAPBOTS       = 2933,
    ACHIEV_NERF_SCRAPBOTS_H     = 2935,
};

//Positional defines 
struct LocationsXY
{
    float x, y, z, o;
    uint32 id;
};

static LocationsXY SummonLoc[]=
{
    {792.706f, 64.033f, 409.632f},  // lower left
    {879.750f, 64.815f, 409.804f},  // upper left
    {896.488f, -93.018f, 409.731f}, // upper right
    {791.016f, -83.516f, 409.804f}, // lower right
};

// void zone
struct MANGOS_DLL_DECL mob_voidzoneAI : public ScriptedAI
{
    mob_voidzoneAI(Creature* pCreature) : ScriptedAI(pCreature) 
    {
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        pCreature->setFaction(14);
        SetCombatMovement(false);
        Reset();
    }

    uint32 Spell_Timer;
    bool m_bIsRegularMode;
    SpellEntry const *spellInfo;

    void Reset()
    {
        spellInfo = (SpellEntry*)GetSpellStore()->LookupEntry(m_bIsRegularMode ? SPELL_VOIDZONE : SPELL_VOIDZONE_H);
        Spell_Timer = 1000;
    }

    void UpdateAI(const uint32 diff)
    {
		// should be an aura here. Couldn't find it
		// hacky way, needs fixing!
        if (Spell_Timer < diff)
        {
            if (spellInfo)
            {
                int32 damage = spellInfo->CalculateSimpleValue(EFFECT_INDEX_1);
                m_creature->CastCustomSpell(m_creature, SPELL_VOIDZONE_EFFECT, &damage, 0, 0, true);
            }
            Spell_Timer = 1000;
        }else Spell_Timer -= diff;  
    }
};

CreatureAI* GetAI_mob_voidzone(Creature* pCreature)
{
    return new mob_voidzoneAI(pCreature);
}

// lifespark
struct MANGOS_DLL_DECL mob_lifesparkAI : public ScriptedAI
{
    mob_lifesparkAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        // should be fixed in DB
        if(!pCreature->GetMap()->IsRegularDifficulty())
            pCreature->SetHealth(176400);
        pCreature->setFaction(14);
        Reset();
    }

    uint32 m_uiShockTimer;

    void Reset()
    {
        m_uiShockTimer = 2000;
        DoCast(m_creature, SPELL_STATIC_CHARGED);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiShockTimer <= diff)
        {
            if (m_creature->IsWithinDistInMap(m_creature->getVictim(), 5))
            {
                DoCast(m_creature->getVictim(), SPELL_SHOCK, true);
                m_uiShockTimer = 2000;
            }
        }
        else m_uiShockTimer -= diff;
    }
};

CreatureAI* GetAI_mob_lifespark(Creature* pCreature)
{
    return new mob_lifesparkAI(pCreature);
}

// XM-024 Pummeller
struct MANGOS_DLL_DECL mob_pummelerAI : public ScriptedAI
{
    mob_pummelerAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint32 Spell_Timer;

    void Reset()
    {
        Spell_Timer = urand(5000, 10000);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (Spell_Timer < diff)
        {
            switch(urand(0, 2))
            {
            case 0:
                DoCast(m_creature->getVictim(), SPELL_CLEAVE);
                break;
            case 1:
                DoCast(m_creature->getVictim(), SPELL_TRAMPLE);
                break;
            case 2:
                DoCast(m_creature->getVictim(), SPELL_UPPERCUT);
                break;
            }
            Spell_Timer = urand(5000, 10000);
        }else Spell_Timer -= diff;        

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_pummeler(Creature* pCreature)
{
    return new mob_pummelerAI(pCreature);
}

// XE-321 Boombot
struct MANGOS_DLL_DECL mob_boombotAI : public ScriptedAI
{
    mob_boombotAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    uint32 m_uiCheckTimer;

    void Reset()
    {
        m_uiCheckTimer = 1000;
    }

    void DamageTaken(Unit* pDoneBy, uint32& uiDamage)
    {
        if (uiDamage > m_creature->GetHealth())
        {
            uiDamage = 0;
            DoCast(m_creature, SPELL_BOOM);
        }
    }

    void DoMeleeAttackIfReady()
    {
        //If we are within range melee the target
        if (m_creature->IsWithinDistInMap(m_creature->getVictim(), ATTACK_DISTANCE))
            DoCast(m_creature, SPELL_BOOM);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiCheckTimer <= uiDiff)
        {
            if (m_pInstance)
            {
                Creature *pXT = m_creature->GetMap()->GetCreature(m_pInstance->GetData64(NPC_XT002));
                if (pXT && m_creature->IsInRange(pXT, 0.0f, INTERACTION_DISTANCE))
                    DoCast(m_creature, SPELL_BOOM);
            }
            m_uiCheckTimer = 1000;
        }else m_uiCheckTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_boombot(Creature* pCreature)
{
    return new mob_boombotAI(pCreature);
}

struct MANGOS_DLL_DECL mob_scrap_botAI : public ScriptedAI
{
    mob_scrap_botAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    uint32 m_uiCheckTimer;
    
    void Reset()
    {
        m_uiCheckTimer = 1000;
    }
    void MoveInLineOfSight(Unit* pWho){}
    void AttackStart(Unit *pWho){}
    void UpdateAI(const uint32 uiDiff)
    {
        if (m_uiCheckTimer <= uiDiff)
        {
            if (m_pInstance)
            {
                Creature *pXT = m_creature->GetMap()->GetCreature(m_pInstance->GetData64(NPC_XT002));
                if (pXT && m_creature->IsInRange(pXT, 0.0f, INTERACTION_DISTANCE))
                {
                    //DoCast(pXT, SPELL_SCRAP_REPAIR, true);
                    uint32 new_health = pXT->GetHealth() + pXT->GetMaxHealth() * 0.01;
                    uint32 max_health = pXT->GetMaxHealth();
                    pXT->SetHealth(new_health > max_health ? max_health : new_health);
                    DoScriptText(EMOTE_REPAIR, pXT);
                    m_creature->DealDamage(m_creature, m_creature->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
                }
            }
            m_uiCheckTimer = 1000;
        }else m_uiCheckTimer -= uiDiff;
    }
};

CreatureAI* GetAI_mob_scrap_bot(Creature* pCreature)
{
    return new mob_scrap_botAI(pCreature);
}

// Heart of the Deconstructor
struct MANGOS_DLL_DECL mob_xtheartAI : public ScriptedAI
{
    mob_xtheartAI(Creature* pCreature) : ScriptedAI(pCreature) 
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        SetCombatMovement(false);
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiDeathTimer;
    uint32 m_uiTotalDamage;

    void Reset()
    {
        DoCast(m_creature, SPELL_EXPOSED_HEART);
        m_creature->SetRespawnDelay(7*DAY*IN_MILLISECONDS);
        m_uiTotalDamage = 0;
        m_uiDeathTimer = 30000;
    }

    void DamageTaken(Unit* pDoneBy, uint32& uiDamage)
    {
        m_uiTotalDamage += uiDamage;
        // double damage
        uiDamage += uiDamage;
    }

    void JustDied(Unit* pKiller)
    {
        if(m_pInstance)
            m_pInstance->SetData(TYPE_XT002_HARD, IN_PROGRESS);
    }

    void UpdateAI(const uint32 diff)
    {
        // despawns the creature if not killed in 30 secs
        if(m_uiDeathTimer < diff)
        {
            // pass damage to boss
            if (Creature* pTemp = m_creature->GetMap()->GetCreature( m_pInstance->GetData64(NPC_XT002)))
            {
                if (pTemp->isAlive())
                    pTemp->DealDamage(pTemp, m_uiTotalDamage, NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
            }
            m_creature->ForcedDespawn();
        }
        else
            m_uiDeathTimer -= diff;
    }
};

CreatureAI* GetAI_mob_xtheart(Creature* pCreature)
{
    return new mob_xtheartAI(pCreature);
}

//XT-002 Deconstructor
struct MANGOS_DLL_DECL boss_xt_002AI : public ScriptedAI
{
    boss_xt_002AI(Creature* pCreature) : ScriptedAI(pCreature) 
    {
        m_pInstance = (instance_ulduar*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    instance_ulduar* m_pInstance;
    bool m_bIsRegularMode;

    std::list<uint64> m_lScrapbotsGUIDList;
    std::list<uint64> m_lBoombotsGUIDList;
    std::list<uint64> m_lPummelerGUIDList;
    std::list<uint64> m_lLifeSparkGUIDList;
    std::list<uint64> m_lVoidZoneGUIDList;

    // spell timers
    uint32 m_uiHeart_Timer;
    uint32 m_uiBomb_Timer;
    uint32 m_uiTantrum_Timer;
    uint32 m_uiEnrage_Timer;

    // summon timers
    uint32 m_uiScrapbotTimer;
    uint32 m_uiBoombotTimer;
    uint32 m_uiPummellerTimer;
    uint32 m_uiScrapbotCount;
    uint32 m_uiBoombotCount;
    uint32 m_uiPummellerCount;
    uint32 m_uiMaxScrapbot;
    uint32 m_uiMaxBoombot;

    // health timers
    uint32 m_uiHealthPercent;
    bool m_bIsEnrage;
    bool m_bPhase2;

    uint64 m_uiXtHeartGUID;

    bool m_bIsHardMode;
    bool m_bCastLightBomb;

    void Reset()
    {
        // spell timers
        m_uiBomb_Timer          = 8000;
        m_uiTantrum_Timer       = 35000;
        m_uiEnrage_Timer        = (m_bIsRegularMode ? 6 : 8)*MINUTE*IN_MILLISECONDS;

        // summon timers
        m_uiScrapbotTimer       = 5000;
        m_uiBoombotTimer        = 5000;
        m_uiPummellerTimer      = 5000;
        m_uiScrapbotCount       = 0;
        m_uiBoombotCount        = 0;
        m_uiPummellerCount      = 0;
        m_uiMaxScrapbot         = 0;
        m_uiMaxBoombot          = 0;
        // health timers
        m_uiHealthPercent       = 75;

        m_bCastLightBomb        = false;
        m_bIsEnrage             = false;
        m_bPhase2               = false;
        m_bIsHardMode           = false;

        m_uiXtHeartGUID         = 0;
        m_lScrapbotsGUIDList.clear();
        m_lBoombotsGUIDList.clear();
        m_lPummelerGUIDList.clear();
        m_lLifeSparkGUIDList.clear();
        m_lVoidZoneGUIDList.clear();

        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetStandState(UNIT_STAND_STATE_STAND);

        if (!m_pInstance)
            return;

        m_pInstance->SetData(TYPE_XT002_HARD, NOT_STARTED);

        DespawnAdds();
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_XT002, FAIL);
    }

    void JustDied(Unit* pKiller)
    {
        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_XT002, DONE);

            if(m_bIsHardMode)
                m_pInstance->SetData(TYPE_XT002_HARD, DONE);
        }

        DoScriptText(SAY_DEATH, m_creature);
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

        DespawnAdds();
    }

    void Aggro(Unit* pWho)
    {
        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_XT002, IN_PROGRESS);

            if(m_pInstance->GetData(TYPE_XT002_TP) != DONE)
                m_pInstance->SetData(TYPE_XT002_TP, DONE);
        }

        DoScriptText(SAY_AGGRO, m_creature);
    }

    void JustSummoned(Creature *pCreature)
    {
        if (!pCreature)
            return;

        switch (pCreature->GetEntry())
        {
            case NPC_LIFESPARK:
                m_lLifeSparkGUIDList.push_back(pCreature->GetGUID());
                break;
            case NPC_VOIDZONE:
                m_lVoidZoneGUIDList.push_back(pCreature->GetGUID());
                break;
        }
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(SAY_SLAY_01 - urand(0, 1), m_creature);
    }

    void SpellHit(Unit *pCaster, const SpellEntry *spellInfo)
    {
        if (spellInfo->Id == SPELL_HEARTBREAK || spellInfo->Id == SPELL_HEARTBREAK_H)
        {
            m_creature->SetHealth(m_creature->GetMaxHealth()+ (m_creature->GetMaxHealth() * (m_bIsRegularMode ? 0.5f : 0.6f)));
            m_bIsHardMode = true;
            m_bPhase2 = false;
        }
    }

    void DespawnAdds()
    {
        DespawnUnitsFromList(m_lScrapbotsGUIDList);
        DespawnUnitsFromList(m_lBoombotsGUIDList);
        DespawnUnitsFromList(m_lPummelerGUIDList);
        DespawnUnitsFromList(m_lLifeSparkGUIDList);
        DespawnUnitsFromList(m_lVoidZoneGUIDList);
    }

    void DespawnUnitsFromList(std::list<uint64> list)
    {
        if (!m_pInstance)
            return;

        if (!list.empty())
        {
            for (std::list<uint64>::iterator i = list.begin(); i != list.end(); i++)
            {
                Creature *pTmp = m_pInstance->instance->GetCreature(*i);
                if (pTmp && pTmp->isAlive())
                    pTmp->DealDamage(pTmp, pTmp->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NONE, NULL, false);
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // both phases
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Hard mode check
        if (m_pInstance->GetData(TYPE_XT002_HARD) == IN_PROGRESS && !m_bIsHardMode)
        {
            DoScriptText(SAY_HEART_CLOSE, m_creature);
            m_creature->SetStandState(UNIT_STAND_STATE_STAND);
            m_creature->RemoveAurasDueToSpell(SPELL_STUN);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            m_creature->AI()->AttackStart(m_creature->getVictim());

            DoCast(m_creature, m_bIsRegularMode ? SPELL_HEARTBREAK : SPELL_HEARTBREAK_H, true);
        }

        // Phase 1
        if (!m_bPhase2)
        {
            // Light/Gravity Bomb
            if (m_uiBomb_Timer < uiDiff)
            {
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
                {
                    if (m_bCastLightBomb)
                        DoCast(pTarget, m_bIsRegularMode ? SPELL_LIGHT_BOMB : SPELL_LIGHT_BOMB_H, true);
                    else
                        DoCast(pTarget, m_bIsRegularMode ? SPELL_GRAVITY_BOMB : SPELL_GRAVITY_BOMB_H, true);

                    m_bCastLightBomb = !m_bCastLightBomb;
                }
                m_uiBomb_Timer = 8000;
            }
            else m_uiBomb_Timer -= uiDiff;

            // Tympanic Tantrum
            if (m_uiTantrum_Timer < uiDiff)
            {
                DoCast(m_creature, SPELL_TANTRUM);
                DoScriptText(SAY_TANTRUM, m_creature);
                m_uiTantrum_Timer = 60000;
            }else m_uiTantrum_Timer -= uiDiff;

            // enrage timer
            if (m_uiEnrage_Timer < uiDiff && !m_bIsEnrage)
            {
                DoCast(m_creature, SPELL_ENRAGE, true);
                if (m_creature->HasAura(SPELL_ENRAGE))
                {
                    m_bIsEnrage = true;
                    DoScriptText(SAY_BERSERK, m_creature);
                }
                else
                    m_uiEnrage_Timer = 5000;
            }else m_uiEnrage_Timer -= uiDiff;

            if (m_creature->GetHealthPercent() < m_uiHealthPercent && !m_bIsHardMode)
            {
                m_uiHeart_Timer = 30000;
                m_creature->CastStop();
                m_uiHealthPercent = m_uiHealthPercent - 25;
                m_bPhase2 = true;
                DoScriptText(SAY_HEART_OPEN, m_creature);
                DoCast(m_creature, SPELL_STUN, true);
                DoScriptText(EMOTE_HEART, m_creature);
                m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);
                m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

                // timers
                m_uiScrapbotTimer       = urand(3000, 5000);
                m_uiBoombotTimer        = urand(3000, 5000);
                m_uiPummellerTimer      = 5000;
                m_uiMaxScrapbot         = urand(7, 10) * 5;
                m_uiMaxBoombot          = urand(3, 7);
                m_uiScrapbotCount       = 0;
                m_uiBoombotCount        = 0;   
                m_uiPummellerCount      = 0;

                if(Creature *Heart = m_creature->SummonCreature(NPC_HEART, 0.0f, 0.0f, 0.0f, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 900000))
                {
                    m_uiXtHeartGUID = Heart->GetGUID();
                    Heart->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    Heart->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                }
            }

            DoMeleeAttackIfReady();
        }
        // Phase 2 - Heart phase
        else
        {
        if (m_uiHeart_Timer < uiDiff)
        {
            DoScriptText(SAY_HEART_CLOSE, m_creature);
            m_creature->SetStandState(UNIT_STAND_STATE_STAND);
            m_creature->RemoveAurasDueToSpell(SPELL_STUN);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            m_creature->AI()->AttackStart(m_creature->getVictim());
            m_bPhase2 = false;
        }
        else m_uiHeart_Timer -= uiDiff;

        //adds
        if(!m_bIsHardMode)
        {
            // pummeller
            if(m_uiPummellerTimer < uiDiff && m_uiPummellerCount < 2)
            {
                if(m_uiPummellerCount == 0)
                    DoScriptText(SAY_ADDS, m_creature);
                uint8 i = urand(0, 4);
                if (Creature* pTemp = m_creature->SummonCreature(NPC_PUMMELER, SummonLoc[i].x + urand(0, 10), SummonLoc[i].y + urand(0, 10), SummonLoc[i].z, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000))
                {
                    DoCast(pTemp, SPELL_ENERGY_ORB, true);
                    if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                    {
                        pTemp->AddThreat(pTarget,0.0f);
                        pTemp->AI()->AttackStart(pTarget);
                        m_lPummelerGUIDList.push_back(pTemp->GetGUID());
                    }
                }
                m_uiPummellerCount += 1;
                m_uiPummellerTimer = 4000;
            }
            else m_uiPummellerTimer -= uiDiff;

            // boombot
            if(m_uiBoombotTimer < uiDiff && m_uiBoombotCount < m_uiMaxBoombot)
            {
                uint8 i = urand(0, 4);
                if (Creature* pTemp = m_creature->SummonCreature(NPC_BOOMBOT, SummonLoc[i].x + urand(0, 10), SummonLoc[i].y + urand(0, 10), SummonLoc[i].z, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000))
                {
                    DoCast(pTemp, SPELL_ENERGY_ORB, true);
                    pTemp->AddThreat(m_creature->getVictim(),1000.0f);
                    pTemp->AI()->AttackStart(m_creature->getVictim());
                    m_lBoombotsGUIDList.push_back(pTemp->GetGUID());
                }
                m_uiBoombotCount += 1;
                m_uiBoombotTimer = 4000;
            }
            else m_uiBoombotTimer -= uiDiff;

            // scrapbot
            if(m_uiScrapbotTimer < uiDiff && m_uiScrapbotCount < m_uiMaxScrapbot)
            {
                uint8 i = urand(0, 4);
                for(int j = 0; j < 5; j++)
                {
                    if (Creature* pTemp = m_creature->SummonCreature(NPC_SCRAPBOT, SummonLoc[i].x + urand(0, 10), SummonLoc[i].y + urand(0, 10), SummonLoc[i].z, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000))
                    {
                        if (!j)
                            DoCast(pTemp, SPELL_ENERGY_ORB, true);
                        pTemp->GetMotionMaster()->Clear();
                        pTemp->GetMotionMaster()->MoveFollow(m_creature, 0, 0);
                        m_lScrapbotsGUIDList.push_back(pTemp->GetGUID());
                        m_uiScrapbotCount += 1;
                    }
                }
                m_uiScrapbotTimer = 3000;
            }
            else m_uiScrapbotTimer -= uiDiff;
        }
        }
    }
};

CreatureAI* GetAI_boss_xt_002(Creature* pCreature)
{
    return new boss_xt_002AI(pCreature);
}

void AddSC_boss_xt_002()
{
    Script* NewScript;

    NewScript = new Script;
    NewScript->Name = "boss_xt_002";
    NewScript->GetAI = GetAI_boss_xt_002;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "mob_xtheart";
    NewScript->GetAI = &GetAI_mob_xtheart;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "mob_pummeler";
    NewScript->GetAI = &GetAI_mob_pummeler;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "mob_boombot";
    NewScript->GetAI = &GetAI_mob_boombot;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "mob_scrap_bot";
    NewScript->GetAI = &GetAI_mob_scrap_bot;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "mob_voidzone";
    NewScript->GetAI = &GetAI_mob_voidzone;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "mob_lifespark";
    NewScript->GetAI = &GetAI_mob_lifespark;
    NewScript->RegisterSelf();
}

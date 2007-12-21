/* Copyright (C) 2006,2007 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: Taerar
SD%Complete: 90
SDComment: Mark of Nature & Teleport NYI
SDCategory: Bosses
EndScriptData */

#include "../sc_defines.h"

//Spells of Taerar

#define SPELL_SLEEP                24777
#define SPELL_NOXIOUSBREATH        24818
#define SPELL_TAILSWEEP            15847
//#define SPELL_MARKOFNATURE         25040                    // Not working
#define SPELL_ARCANEBLAST          24857
#define SPELL_BELLOWINGROAR        22686
#define SPELL_SUMMONSHADE          24843


//Spells of Shades of Taerar

#define SPELL_POSIONCLOUD                24840      
#define SPELL_POSIONBREATH             20667   

struct MANGOS_DLL_DECL boss_taerarAI : public ScriptedAI
{
    boss_taerarAI(Creature *c) : ScriptedAI(c) {EnterEvadeMode();}

    uint32 Sleep_Timer;
    uint32 NoxiousBreath_Timer;
    uint32 TailSweep_Timer;
    //uint32 MarkOfNature_Timer;
    uint32 ArcaneBlast_Timer;
    uint32 BellowingRoar_Timer;
    uint32 Shades_Timer;
    uint32 Summon1_Timer;
    uint32 Summon2_Timer;
    uint32 Summon3_Timer;
    int Rand;
    int RandX;
    int RandY;
    Creature* Summoned;
    bool InCombat;
    bool Shades;

    void EnterEvadeMode()
    {       
        Sleep_Timer = 15000;
        NoxiousBreath_Timer = 8000;
        TailSweep_Timer = 4000;
        //MarkOfNature_Timer = 45000;
        ArcaneBlast_Timer = 12000;
        BellowingRoar_Timer = 30000;
        Summon1_Timer = 0;
        Summon2_Timer = 0;
        Summon3_Timer = 0;
        Shades_Timer = 60000;                               //The time that Taerar is banished
        InCombat = false;
        Shades = false; 

        m_creature->RemoveAllAuras();
        m_creature->DeleteThreatList();
        m_creature->CombatStop();
        DoGoHome();
        m_creature->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_DISARM, true);
    }

    void AttackStart(Unit *who)
    {
        if (!who)
            return;

        if (who->isTargetableForAttack() && who!= m_creature)
        {
            //Begin melee attack if we are within range
            DoStartMeleeAttack(who);
            InCombat = true;
        }
    }

    void MoveInLineOfSight(Unit *who)
    {
        if (!who || m_creature->getVictim())
            return;

        if (who->isTargetableForAttack() && who->isInAccessablePlaceFor(m_creature) && m_creature->IsHostileTo(who))
        {
            float attackRadius = m_creature->GetAttackDistance(who);
            if (m_creature->IsWithinDistInMap(who, attackRadius) && m_creature->GetDistanceZ(who) <= CREATURE_Z_ATTACK_RANGE && m_creature->IsWithinLOSInMap(who))
            {
                if(who->HasStealthAura())
                    who->RemoveSpellsCausingAura(SPELL_AURA_MOD_STEALTH);

                DoStartMeleeAttack(who);
                InCombat = true;

            }
        }
    }

    void SummonShades(Unit* victim)
    {
        Rand = rand()%15;
        switch (rand()%2)
        {
        case 0: RandX = 0 - Rand; break;
        case 1: RandX = 0 + Rand; break;
        }
        Rand = 0;
        Rand = rand()%15;
        switch (rand()%2)
        {
        case 0: RandY = 0 - Rand; break;
        case 1: RandY = 0 + Rand; break;
        }
        Rand = 0;
        Summoned = DoSpawnCreature(15302, RandX, RandY, 0, 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300000);
        if(Summoned)
            ((CreatureAI*)Summoned->AI())->AttackStart(victim);
    }

    void UpdateAI(const uint32 diff)
    {
        if (Shades && Shades_Timer < diff)
        {
            //Become unbanished again 
            m_creature->setFaction(14);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            //m_creature->m_canMove = true;
            Shades = false;
        } else if (Shades)
        {
            Shades_Timer -= diff;
            //Do nothing while banished
            return;
        }

        //Return since we have no target
        if (!m_creature->SelectHostilTarget() || !m_creature->getVictim())
            return;

        //Sleep_Timer
        if (Sleep_Timer < diff)
        {
            //Cast
            Unit* target = NULL;

            target = SelectUnit(SELECT_TARGET_RANDOM,0);
            if (target)DoCast(target,SPELL_SLEEP);

            //14 seconds
            Sleep_Timer = 14000;
        }else Sleep_Timer -= diff;

        //NoxiousBreath_Timer
        if (NoxiousBreath_Timer < diff)
        {
            //Cast
            DoCast(m_creature->getVictim(),SPELL_NOXIOUSBREATH);

            //20 seconds until we should cast this agian
            NoxiousBreath_Timer = 14000 + rand()%6000;
        } else NoxiousBreath_Timer -= diff;


        //Tailsweep every 2 seconds
        if (TailSweep_Timer < diff)
        {
            Unit* target = NULL;
            target = SelectUnit(SELECT_TARGET_RANDOM,0);                    
            //Only cast if we are behind
            if (!m_creature->HasInArc( M_PI, target))
                DoCast(target,SPELL_TAILSWEEP);
            TailSweep_Timer = 2000;
        }else TailSweep_Timer -= diff;

        //             //MarkOfNature_Timer
        //            if (MarkOfNature_Timer < diff)
        //             {
        //                 //Cast
        //                 DoCast(m_creature->getVictim(),SPELL_MARKOFNATURE);
        // 
        //                 //45 seconds until we should cast this agian
        //                 MarkOfNature_Timer = 45000;
        //             }else MarkOfNature_Timer -= diff;

        //ArcaneBlast_Timer
        if (ArcaneBlast_Timer < diff)
        {
            //Cast
            DoCast(m_creature->getVictim(),SPELL_ARCANEBLAST);

            //11 seconds until we should cast this agian
            ArcaneBlast_Timer = 7000 + rand()%5000;
        }else ArcaneBlast_Timer -= diff;

        //BellowingRoar_Timer
        if (BellowingRoar_Timer < diff)
        {
            //Cast
            DoCast(m_creature->getVictim(),SPELL_BELLOWINGROAR);

            //18 seconds until we should cast this agian
            BellowingRoar_Timer = 30000;
        } else BellowingRoar_Timer -= diff;


        //Summon 3 Shades
        if ( !Shades  && (int) (m_creature->GetHealth()*100 / m_creature->GetMaxHealth() +0.5) == 75)
        {

            if (Summon1_Timer < diff)
            {

                //Inturrupt any spell casting
                m_creature->InterruptSpell(CURRENT_GENERIC_SPELL);
                m_creature->setFaction(35);
                m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                //m_creature->m_canMove = false;

                //Cast
                Unit* target = NULL;
                target = SelectUnit(SELECT_TARGET_RANDOM,0);
                SummonShades(target);
                SummonShades(target);
                SummonShades(target);
                Summon1_Timer = 120000;
                Shades = true;
                Shades_Timer = 60000;
            } else Summon1_Timer -= diff;
        }

        //Summon 3 Shades
        if ( !Shades  && (int) (m_creature->GetHealth()*100 / m_creature->GetMaxHealth() +0.5) == 50)
        {

            if (Summon2_Timer < diff)
            {

                //Inturrupt any spell casting
                m_creature->InterruptSpell(CURRENT_GENERIC_SPELL);
                m_creature->setFaction(35);
                m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                //m_creature->m_canMove = false;

                //Cast
                Unit* target = NULL;
                target = SelectUnit(SELECT_TARGET_RANDOM,0);
                SummonShades(target);
                SummonShades(target);
                SummonShades(target);
                Summon2_Timer = 120000;
                Shades = true;
                Shades_Timer = 60000;
            } else Summon2_Timer -= diff;
        }

        //Summon 3 Shades
        if ( !Shades  && (int) (m_creature->GetHealth()*100 / m_creature->GetMaxHealth() +0.5) == 25)
        {
            if (Summon3_Timer < diff)
            {
                //Inturrupt any spell casting
                m_creature->InterruptSpell(CURRENT_GENERIC_SPELL);
                m_creature->setFaction(35);
                m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                //m_creature->m_canMove = false;

                //Cast
                Unit* target = NULL;
                target = SelectUnit(SELECT_TARGET_RANDOM,0);
                SummonShades(target);
                SummonShades(target);
                SummonShades(target);
                Summon3_Timer = 120000;
                Shades = true;
                Shades_Timer = 60000;
            } else Summon3_Timer -= diff;
        }

        DoMeleeAttackIfReady();
    }
};


// Shades of Taerar Script

struct MANGOS_DLL_DECL boss_shadeoftaerarAI : public ScriptedAI
{
    boss_shadeoftaerarAI(Creature *c) : ScriptedAI(c) {EnterEvadeMode();}

    uint32 PoisonCloud_Timer;
    uint32 PosionBreath_Timer;
    bool InCombat;

    void EnterEvadeMode()
    {       
        PoisonCloud_Timer = 8000;
        PosionBreath_Timer = 12000;
        InCombat = false;

        m_creature->RemoveAllAuras();
        m_creature->DeleteThreatList();
        m_creature->CombatStop();
        DoGoHome();
    }

    void AttackStart(Unit *who)
    {
        if (!who)
            return;

        if (who->isTargetableForAttack() && who!= m_creature)
        {
            //Begin melee attack if we are within range
            DoStartMeleeAttack(who);
            InCombat = true;
        }
    }

    void MoveInLineOfSight(Unit *who)
    {
        if (!who || m_creature->getVictim())
            return;

        if (who->isTargetableForAttack() && who->isInAccessablePlaceFor(m_creature) && m_creature->IsHostileTo(who))
        {
            float attackRadius = m_creature->GetAttackDistance(who);
            if (m_creature->IsWithinDistInMap(who, attackRadius) && m_creature->GetDistanceZ(who) <= CREATURE_Z_ATTACK_RANGE && m_creature->IsWithinLOSInMap(who))
            {
                if(who->HasStealthAura())
                    who->RemoveSpellsCausingAura(SPELL_AURA_MOD_STEALTH);

                DoStartMeleeAttack(who);
                InCombat = true;

            }
        }
    }

    void UpdateAI(const uint32 diff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostilTarget() || !m_creature->getVictim())
            return;

        //PoisonCloud_Timer
        if (PoisonCloud_Timer < diff)
        {
            //Cast
            DoCast(m_creature->getVictim(),SPELL_POSIONCLOUD);

            //30 seconds
            PoisonCloud_Timer = 30000;
        }else PoisonCloud_Timer -= diff;

        //PosionBreath_Timer
        if (PosionBreath_Timer < diff)
        {
            //Cast
            DoCast(m_creature->getVictim(),SPELL_POSIONBREATH);

            //12 seconds until we should cast this agian
            PosionBreath_Timer = 12000;
        }else PosionBreath_Timer -= diff;

        DoMeleeAttackIfReady();
    }
}; 

CreatureAI* GetAI_boss_taerar(Creature *_Creature)
{
    return new boss_taerarAI (_Creature);
}

CreatureAI* GetAI_boss_shadeoftaerar(Creature *_Creature)
{
    return new boss_shadeoftaerarAI (_Creature);
}

void AddSC_boss_taerar()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name="boss_taerar";
    newscript->GetAI = GetAI_boss_taerar;
    m_scripts[nrscripts++] = newscript;

    newscript = new Script;
    newscript->Name="boss_shade_of_taerar";
    newscript->GetAI = GetAI_boss_shadeoftaerar;
    m_scripts[nrscripts++] = newscript;
}

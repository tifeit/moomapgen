|60|83 FB **3C** 7D 09 83 F9 64  0F 85 67 00 00 00 83 FB|
|:-|:---------------------------------------------------|
|80|83 FB **50** 7D 05 83 F9 64  75 5D 30 C0 83 FB 5A 7D|
|90|83 FB **5A** 7D 05 83 F9 64  75 02 B0 01 8B 55 A4 0F|

|70|83 FB **46** 7D 05 83 F9 64  75 36 8B 45 E8 89 45 FC| для саботажа|
|:-|:---------------------------------------------------|:-----------------------|
|90|83 FB **5A** 7D 05 83 F9 64  75 15 0F BF 55 E0 0F BF| для саботажа|
```

void __fastcall SPY_Resolve_Player_Spies_(int currentPlayerOffset)
{
  int nOffenderSpyBonus; // ebx@3
  int nOffenderSpies; // edi@3
  int ptrOffenderPlayer; // esi@3
  int MOX_player; // esi@3
  int nBonusesDifference; // ebx@4
  int randOffence; // ecx@4
  int nOffenderTotalBonus; // ebx@4
  unsigned __int16 v8; // ax@7
  int randOffence_; // ecx@7
  char v10; // al@15
  int v11; // ecx@25
  int v12; // ebx@25
  unsigned int v13; // esi@25
  unsigned int v14; // ebx@25
  unsigned int v15; // eax@25
  int v16; // edx@25
  __int16 v17; // cx@32
  int v18; // esi@34
  unsigned int v19; // eax@36
  __int16 v20; // si@36
  __int16 v21; // cx@36
  int v22; // [sp-8h] [bp-64h]@32
  int ptrDefenderPlayer; // [sp+0h] [bp-5Ch]@1
  char v24; // [sp+4h] [bp-58h]@36
  __int16 v25; // [sp+6h] [bp-56h]@36
  int v26; // [sp+8h] [bp-54h]@36
  int v27; // [sp+Ch] [bp-50h]@36
  int v28; // [sp+10h] [bp-4Ch]@36
  __int16 v29; // [sp+14h] [bp-48h]@36
  char v30; // [sp+18h] [bp-44h]@32
  __int16 v31; // [sp+1Ah] [bp-42h]@32
  int v32; // [sp+1Ch] [bp-40h]@32
  int v33; // [sp+20h] [bp-3Ch]@32
  int v34; // [sp+24h] [bp-38h]@32
  __int16 v35; // [sp+28h] [bp-34h]@32
  int nOffenderSpyBonus2; // [sp+2Ch] [bp-30h]@3
  int nDefenderSpyBonus; // [sp+30h] [bp-2Ch]@1
  unsigned int randDefence; // [sp+34h] [bp-28h]@4
  int nDefenderTechBonus; // [sp+38h] [bp-24h]@4
  int sizeofSkippedArray; // [sp+3Ch] [bp-20h]@1
  int ptrDefenderSpyBonusArray; // [sp+40h] [bp-1Ch]@1
  int nNumOfPlayers; // [sp+44h] [bp-18h]@1
  int nNumOfSpies; // [sp+48h] [bp-14h]@1
  unsigned int nUnknown; // [sp+4Ch] [bp-10h]@1
  int aPlayers; // [sp+50h] [bp-Ch]@1
  int ptrOffenderSpyBonusArray; // [sp+54h] [bp-8h]@1
  int v47; // [sp+58h] [bp-4h]@21

  ptrDefenderPlayer = currentPlayerOffset;
  sizeofSkippedArray = (currentPlayerOffset - MOX__player) / 3753;
  nNumOfSpies = BILL_Get_Their_Spy_Number_(
                  (currentPlayerOffset - MOX__player) / 3753,
                  (currentPlayerOffset - MOX__player) / 3753);
  nDefenderSpyBonus = SPY_N_Spies_Bonus_(nNumOfSpies);
  nNumOfPlayers = MOX__NUM_PLAYERS;
  ptrDefenderSpyBonusArray = 4 * sizeofSkippedArray;
  aPlayers = 3753 * MOX__NUM_PLAYERS;
  nUnknown = 0;
  ptrOffenderSpyBonusArray = 4 * MOX__NUM_PLAYERS;
  while ( nNumOfPlayers > 0 )
  {
    --nNumOfPlayers;
    aPlayers -= 3753;
    ptrOffenderSpyBonusArray -= 4;
    if ( nNumOfPlayers != sizeofSkippedArray )  // Если это мы сами
    {
      MOX_player = MOX__player;
      nOffenderSpies = BILL_Get_Their_Spy_Number_(nNumOfPlayers, sizeofSkippedArray);
      ptrOffenderPlayer = aPlayers + MOX_player;
      nOffenderSpyBonus = SPY_N_Spies_Bonus_(nOffenderSpies);
      nOffenderSpyBonus2 = nOffenderSpyBonus;
      if ( nOffenderSpies )
      {
        random_Random(100);                     // Рандомное число от 0 до 100, остальные числа значения не несут.
        randDefence = random_Random(100);       // Опять рандомное число он 0 до 100
        nDefenderTechBonus = *(__int16 *)((char *)SPY__spy_bonuses + ptrOffenderSpyBonusArray);
        nOffenderTotalBonus = nDefenderTechBonus + randOffence + nOffenderSpyBonus;
        nDefenderTechBonus = *(__int16 *)((char *)&word_1A4E7A + ptrDefenderSpyBonusArray);
        nBonusesDifference = nOffenderTotalBonus - (nDefenderSpyBonus + nDefenderTechBonus + randDefence);
        if ( *(_BYTE *)(ptrOffenderPlayer + 40) != 100 )
        {
          if ( *(_BYTE *)(ptrDefenderPlayer + 40) == 100 )
            nBonusesDifference += (unsigned __int8)byte_191CB0 - 2;
        }
        v8 = BILL_Get_Their_Spy_Mission_(
               (signed __int16)nNumOfPlayers,
               (signed __int16)sizeofSkippedArray,
               nBonusesDifference);
        if ( v8 < 1u )
        {
          if ( !v8 )
          {
            if ( nBonusesDifference >= 60 || randOffence_ == 100 )
            {
              if ( nBonusesDifference >= 80 || randOffence_ == 100 )
              {
                v10 = 0;
                if ( nBonusesDifference >= 90 || randOffence_ == 100 )
                  v10 = 1;
                SPY_Steal_App_(ptrOffenderPlayer, ptrDefenderPlayer, v10);
              }
            }
          }
        }
        else
        {
          if ( v8 <= 1u )
          {
            if ( nBonusesDifference >= 70 || randOffence_ == 100 )
            {
              v47 = nNumOfPlayers;
              if ( nBonusesDifference >= 90 || randOffence_ == 100 )
                SPY_Frame_Another_((signed __int16)nNumOfPlayers, (signed __int16)sizeofSkippedArray, &v47, -1);
              SPY_Destroy_Random_Building_(
                (signed __int16)nNumOfPlayers,
                (signed __int16)sizeofSkippedArray,
                (signed __int16)v47);
            }
          }
        }
        v14 = random_Random(100);
        v13 = v14;
        v15 = random_Random(100);
        v12 = nOffenderSpyBonus2
            + *(__int16 *)((char *)SPY__spy_bonuses + v16)
            + v14
            - (nDefenderSpyBonus
             + *(__int16 *)((char *)&word_1A4E7A + ptrDefenderSpyBonusArray)
             + v15
             + 20);
        if ( (unsigned __int16)BILL_Get_Their_Spy_Mission_(
                                 (signed __int16)nNumOfPlayers,
                                 (signed __int16)sizeofSkippedArray,
                                 v12) == 2 )
          v12 += 20;
        if ( v12 >= 80 || v13 == 100 )
          ++nUnknown;
        if ( v12 <= -80 || v11 == 100 )
        {
          BILL_Set_Their_Spy_Number_(
            (signed __int16)nNumOfPlayers,
            (signed __int16)sizeofSkippedArray,
            (signed __int16)(nOffenderSpies - 1));
          set386_memset_(&v30, 0, 18);
          v30 = 10;
          v31 = sizeofSkippedArray;
          LOWORD(v22) = v35;
          MSG_Add_Msg_(10, v32, v33, v34, v22, v17);
        }
      }
    }
  }
  JUMPOUT(nUnknown, 0, *(unsigned int *)locret_101195);
  v18 = nNumOfSpies - nUnknown;
  if ( (signed int)(nNumOfSpies - nUnknown) < 0 )
    v18 = 0;
  BILL_Set_Their_Spy_Number_(
    (signed __int16)sizeofSkippedArray,
    (signed __int16)sizeofSkippedArray,
    (signed __int16)v18);
  v19 = nNumOfSpies - v18;
  v20 = nNumOfSpies - v18;
  JUMPOUT(v19, 0, *(unsigned int *)locret_101195);
  set386_memset_(&v24, 0, 18);
  v25 = v20;
  v24 = 11;
  LOWORD(v22) = v29;
  MSG_Add_Msg_(11, v26, v27, v28, v22, v21);
  JUMPOUT(*(unsigned int *)locret_101195);
}
```

//Officer bonuses
```
int __fastcall SPY_Compute_Spy_Bonuses_(int a1, int a2)
{
  int v2; // ecx@1
  int v3; // ebx@1
  int v4; // esi@1
  int v5; // edi@2
  int v6; // eax@5
  int Officer_spy_bonus; // edi@5
  int v8; // eax@11
  int v9; // eax@12
  int result; // eax@19
  int v11; // ST08_4@19
  int v12; // [sp+0h] [bp-18h]@1
  int v13; // [sp+4h] [bp-14h]@1
  int v14; // [sp+Ch] [bp-Ch]@5
  int v15; // [sp+10h] [bp-8h]@1

  v4 = a2;
  v13 = 0;
  v15 = 0;
  v12 = 10 * *(a1 + 2232) + *(a1 + 2216) + SPY_Tech_Spy_Bonus_(a1);
  v3 = MOX__leaders + 3953;
  while ( v3 > MOX__leaders )
  {
    v5 = *(v3 - 1);
    v3 -= 59;
    if ( v5 == (v2 - MOX__player) / 3753 && *(v3 + 57) < 3u && !COLCALC_Leader_At_Anomaly_(v3) )
    {
      v6 = (v3 - MOX__leaders) / 59;
      Officer_spy_bonus = 0;
      v14 = 0;
      if ( *(v3 + 39) & 0x80 )
      {
        Officer_spy_bonus = 3 * (OFFICER_Owned_Officer_Level_(v6) + 1);
      }
      else
      {
        if ( *(v3 + 39) & 0x40 )
          Officer_spy_bonus = 2 * OFFICER_Owned_Officer_Level_(v6) + 2;
      }
      if ( Officer_spy_bonus > v13 )
        v13 = Officer_spy_bonus;
      v8 = (v3 - MOX__leaders) / 59;
      if ( *(v3 + 40) & 2 )
      {
        v9 = 3 * OFFICER_Owned_Officer_Level_(v8);
LABEL_15:
        v14 = v9;
        goto LABEL_16;
      }
      if ( *(v3 + 40) & 1 )
      {
        v9 = 2 * OFFICER_Owned_Officer_Level_(v8);
        goto LABEL_15;
      }
LABEL_16:
      if ( v15 < v14 )
        v15 = v14;
    }
  }
  *v4 = v13 + v12;
  LOWORD(v3) = byte_100A36[*(v2 + 2207)];
  result = v3 + v15 + v12;
  *v11 = result;
  return result;
}
```
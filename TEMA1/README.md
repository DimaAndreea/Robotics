# TEMA 1: EV Charger
## Descrierea temei:
   - Această temă simulează o stație de încărcare pentru un vehicul electric. Circuitul implementat folosește mai multe LED-uri și butoane.  
   - Circuitul conține un LED RGB ce reprezintă disponibilitatea stației (verde - disponibil; roșu - încărcarea e activă).  
   - De asemenea, nivelul de încărcare al bateriei este reprezentat de 4 LED-uri:  
     - primul LED → 25%  
     - al doilea LED → 50%  
     - al treilea LED → 75%  
     - al patrulea LED → 100%  
   
   - Încărcarea începe prin apăsarea butonului de **START** (apăsarea acestui buton în timpul încărcării nu face nimic).  
   - Primul LED clipește de 2 ori, iar a treia oară rămâne aprins, când în același timp se trece la următorul LED care începe și el să clipească. Acest proces continuă până când se ajunge la ultimul LED, care clipește de 2 ori și se stinge.  
   - Fiecare LED clipește timp de 3 secunde.  
   - Când încărcarea a ajuns la final, toate cele 4 LED-uri clipeșc de 3 ori simultan, iar LED-ul RGB își schimbă înapoi culoarea din roșu în verde.  
   - Apăsarea lungă a butonului de **STOP** (minim o secundă) oprește forțat procesul de încărcare prin animația de la final (toate LED-urile clipeșc de 3 ori simultan).  

---
  
  ## Componentele folosite:
  - 4x LED-uri (pentru a simula procentul de încărcare)
  - 1x LED RGB (pentru starea de liber sau ocupat)
  - 2x Butoane (pentru start încărcare și stop încărcare)
  - 9x Rezistoare (7x 220ohm, 2x 1K)
  - Breadboard
  - Linii de legătură
---

<details>
  <summary> <b> Schema electrică </b> </summary>

  ## Schema electrica a circuitului implementat pe Tinkercad
  ![Mighty Kup-Curcan](https://github.com/user-attachments/assets/4649d0a3-51a5-43db-80a4-421e06e5231b)
  ##
</details>


<details>
  <summary> <b> Poze ale setup-ului fizic </b> </summary>
  
  ## Poze cu montajul implementat fizic:
  
![2](https://github.com/user-attachments/assets/57d52a8a-8b1a-4fb2-85a3-e7bd840ff5e4)
![1](https://github.com/user-attachments/assets/9ac6d843-cf6b-4d75-a876-5f470fc70938)
![5](https://github.com/user-attachments/assets/68046be3-143e-4fea-ac2c-671b0a263384)
![4](https://github.com/user-attachments/assets/2e1c19be-fc1a-423d-b72f-714b4565a49d)
![3](https://github.com/user-attachments/assets/e2b85a01-59a3-4292-8514-a3a8adf5d7bf)
##
</details>


<details>
  <summary> <b> Video cu montajul fizic </b> </summary>

  ## Link către videoul ce arată funcționalitatea montajului fizic:
  https://www.youtube.com/watch?v=eAE200TeHGY
  ##
</details>

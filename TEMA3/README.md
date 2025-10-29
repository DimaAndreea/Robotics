# TEMA 3: Quick Time

### Coechipier: [@Bogdan-Lungu](https://github.com/Bogdan-Lungu/Robotica)


  ## 1. Descrierea temei:
- Tema presupune crearea unui joc competitiv de reflexe pentru doi jucători, care concurează pentru a obține cel mai mare punctaj, punându-și la încercare viteza de reacție.  
- Proiectul se va desfășura în echipe de câte două persoane, fiecare jucător având butoane și LED-uri proprii.  
- Jocul va include mai multe runde, iar scopul fiecărui jucător este să apese cât mai rapid butonul care corespunde culorii afișate pe LED-ul RGB al echipei sale.  
- Punctajul fiecărui jucător va fi afișat în timp real pe un ecran LCD, iar la final, jucătorul cu cel mai mare punctaj va fi declarat câștigător.  

---

## 2. Desfășurarea jocului:
- Jocul începe cu un mesaj de bun venit afișat pe LCD.  
- Este implementat un buton dedicat pentru pornirea jocului.  
- La fiecare rundă, fiecare jucător este activ pe rând, iar LED-ul RGB al acestuia se aprinde într-o culoare care corespunde unuia dintre butoanele sale.  
- Jucătorul trebuie să apese rapid butonul corect pentru a primi puncte. Cu cât reacționează mai repede, cu atât scorul este mai mare.  
- La finalul fiecărei runde, LCD-ul afișează punctajele ambilor jucători.  

---

## 3. Timpul și finalizarea jocului:
- Pe parcursul jocului, servomotorul se rotește, indicând progresul.  
- O rotație de 180 de grade a servomotorului semnalează sfârșitul jocului, iar LCD-ul afișează numele câștigătorului și scorul final.  
- Ulterior, ecranul revine la mesajul de start.  

---

## Componentele folosite:
- 2x Arduino UNO (ATmega328P microcontroller)  
- 2x Breadboard  
- 6x LED-uri (câte 3 pentru fiecare jucător)  
- 2x LED-uri RGB (1 pentru fiecare jucător)  
- 7x Butoane (câte 3 pentru fiecare jucător + 1 buton de start joc)  
- 22x Rezistoare:  
  - 13x 220 Ω (pentru LED-uri și LCD)  
  - 8x 1K Ω (pentru butoane)  
  - 1x 100 Ω (pentru buzzer)  
- 1x Servomotor  
- 1x LCD  
- 1x Potențiometru  
- 1x Buzzer  
- Fire de legătură  

---


<details>
  <summary> <b> Schema electrică </b> </summary>

  ## Schema electrica a circuitului implementat pe Tinkercad
  ![tema3 - final (1)](https://github.com/user-attachments/assets/a0ed21f9-6a5f-423d-b3f3-7bf24b97e93f)

  ##
</details>


<details>
  <summary> <b> Poze ale setup-ului fizic </b> </summary>
  
  ## Poze cu montajul implementat fizic:
  ![IMG_6150](https://github.com/user-attachments/assets/ade3c7c3-a6c9-42a0-a94f-a53e90d141cb)
![IMG_6148](https://github.com/user-attachments/assets/d99b4c33-b8cc-4933-9b4c-89d433e756ba)
![IMG_6151](https://github.com/user-attachments/assets/2be2de60-1ab2-4fce-a99d-a17e64a2832a)

  ##
</details>


<details>
  <summary> <b> Video cu montajul fizic </b> </summary>

  ## Link către videoul ce arată funcționalitatea montajului fizic:
  https://youtu.be/nyq8nsM4g2E
  ##
</details>

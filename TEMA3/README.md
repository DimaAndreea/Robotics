# TEMA 3: Quick Time

### Coechipier: [@Bogdan-Lungu](https://github.com/Bogdan-Lungu/Robotica)

<details>
  <summary> <b> Despre </b> </summary>

  ## 1. Descrierea temei:
  - Tema presupune crearea unui joc competitiv de reflexe pentru doi jucatori, care concureaza pentru a obtine cel mai mare punctaj, punandu-si la incercare viteza de reactie.
  - Proiectul se va desfasura in echipe de cate doua persoane, fiecare jucator avand butoane si LED-uri proprii.
  - Jocul va include mai multe runde, iar scopul fiecarui jucator este sa apese cat mai rapid butonul care corespunde culorii afisate pe LED-ul RGB al echipei sale.
  - Punctajul fiecarui jucator va fi afisat in timp real pe un ecran LCD, iar la final, jucatorul cu cel mai mare punctaj va fi declarat castigator.

  ## 2. Desfasurarea jocului:
  - Jocul incepe cu un mesaj de bun venit afisat pe LCD.
  - Este implementat un buton dedicat pentru pornirea jocului.
    
  - La fiecare runda, fiecare jucator este activ pe rand, iar LED-ul RGB al acestuia se aprinde intr-o culoare care corespunde unuia dintre butoanele sale.
  - Jucatorul trebuie sa apese rapid butonul corect pentru a primi puncte. Cu cat reactioneaza mai repede, cu atat scorul este mai mare.
  - La finalul fiecarei runde, LCD-ul afiseaza punctajele ambilor jucatori.

  ## 3. Timpul si finalizarea jocului
  - Pe parcursul jocului, servomotorul se roteste, indicand progresul.
  - O rotatie de 180 de grade a servomotorului semnaleaza sfarsitul jocului, iar LCD-ul afiseaza numele castigatorului si scorul final.
  - Ulterior, ecranul revine la mesajul de start.

##
</details>


<details> 
  <summary><b>Componente</b></summary>
  
  ## Componentele folosite:
  - 2x Arduino Uno (ATmega328P microcontroller)
  - 2x Breadbord
  - 6x LED-uri (cate 3 pentru fiecare jucator)
  - 2x LED-uri RGB (1 pentru fiecare jucator)
  - 7x Butoane (cate 3 pentru fiecare jucator + 1 buton de start joc)
  - 22x Rezistoare
    - 13x 220ohm (pentru LED-uri si LCD)
    - 8x 1K (pentru butoane)
    - 1x 100ohm (pentru buzzer)
  - 1x Servomotor
  - 1x LCD
  - 1x Potentiometru
  - 1x Buzzer
  - Linii de legatura
    ##
</details>


<details>
  <summary> <b> Schema electrica </b> </summary>

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

  ## Link catre videoul ce arata functionalitatea montajului fizic:
  https://youtu.be/nyq8nsM4g2E
  ##
</details>

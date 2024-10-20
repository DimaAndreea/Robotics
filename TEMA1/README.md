# TEMA 1

<details>
  <summary><b>Cerinte</b></summary>
  
  ## 1. Detalii Tehnice:
  Led-ul RGB reprezintă disponibilitatea stației. Dacă stația este liberă led-ul va fi verde, iar dacă stația este ocupată se va face roșu.

  Led-urile simple reprezintă gradul de încărcare al bateriei, pe care îl vom simula printr-un loader progresiv (L1 = 25%, L2 = 50%, L3 = 75%, L4 = 100%). Loader-ul se încarcă prin aprinderea succesivă a led-urilor, la un interval fix de 3s. LED-ul care semnifică procentul curent de încărcare va avea starea de clipire, LED-urile din urma lui fiind aprinse continuu, iar celelalte stinse.

  Apăsarea scurtă a butonului de start va porni încărcarea. Apăsarea acestui buton în timpul încărcării nu va face nimic.

  Apăsarea lungă a butonului de stop va opri încărcarea forțat și va reseta stația la starea liberă. Apăsarea acestui buton cât timp stația este liberă nu va face nimic.

  ## 2. Flow:
  Starea stației este ‘liberă’. Loader-ul este stins, iar led-ul pentru disponibilitate este verde.

  Se apasă butonul pentru start.

  Led-ul pentru disponibilitate se face roșu, iar încărcarea începe prin aprinderea primului LED L1.

  Led-ul 1 clipește timp de 3s, celelalte fiind stinse.

  După încărcarea primului procent de 25% led-ul rămâne aprins și se trece la următorul led, care va începe să clipească.

  La finalizarea încărcării toate led-urile vor clipi simultan de 3 ori, iar apoi se vor stinge, pentru a semnaliza finalizarea procesului.

  Led-ul pentru disponibilitate se face verde.

  Dacă oricând de la pornirea încărcării până la finalizarea acesteia este apăsat lung (min 1s) butonul de stop, încărcarea se întrerupe prin animația de final (toate led-urile clipesc de 3 ori), iar led-ul pentru disponibilitate devine verde.

</details>


<details> 
  <summary><b>Componente</b></summary>
  
  ## Componentele folosite:
  - 4x LED-uri (pentru a simula procentul de încărcare)
  - 1x LED RGB (pentru starea de liber sau ocupat)
  - 2x Butoane (pentru start încărcare și stop încărcare)
  - 9x Rezistoare (7x 220ohm, 2x 1K)
  - Breadboard
  - Linii de legătură
</details>


<details>
  <summary> <b> Schema electrica </b> </summary>

  ## Schema electrica a circuitului implementat pe Tinkercad
  ![t725](https://github.com/user-attachments/assets/6c5c1a57-09fd-46ec-bc38-4dc7784aeb1c)
  
</details>


<details>
  <summary> <b> Poze ale setup-ului fizic </b> </summary>
  
  ## Poze cu montajul implementat fizic:
  
![2](https://github.com/user-attachments/assets/57d52a8a-8b1a-4fb2-85a3-e7bd840ff5e4)
![1](https://github.com/user-attachments/assets/9ac6d843-cf6b-4d75-a876-5f470fc70938)
![5](https://github.com/user-attachments/assets/68046be3-143e-4fea-ac2c-671b0a263384)
![4](https://github.com/user-attachments/assets/2e1c19be-fc1a-423d-b72f-714b4565a49d)
![3](https://github.com/user-attachments/assets/e2b85a01-59a3-4292-8514-a3a8adf5d7bf)

</details>


<details>
  <summary> <b> Video cu montajul fizic </b> </summary>

  ## Link catre videoul ce arata functionalitatea montajului fizic:
  https://www.youtube.com/watch?v=eAE200TeHGY
  
</details>

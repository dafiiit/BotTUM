
std::string vector_to_string(const std::vector<int>& numbers) {
    std::stringstream ss;
    for (int number : numbers) {
        ss << number;
    }
    return ss.str();
}

void entferne_wert(int vector[], int wert)
    {
      for (int i = 0; i < vector.size; i++)
      {
        if (vector[i] == wert)
        {
          vector.erase(i);
        }
      }
    }

void loop()
{
    std::sort(zustands_array, zustands_array + 2);

    if (zustands_array[0] == 0 && zustands_array[1] == 0) //wir befinden uns auf Fläche
        Serial.println("Robo befindet sich auf Fläche %i", zustands_array[2]);
        Serial.println("Zum aufstehen auf Kante gebe k ein, zum aufstehen auf eine Ecke e");
        if (Serial.available()){char user_input = serial.read();}
        if (user_input == k)
        {
            std::auswahl_array[6] = {1, 2, 3, 4, 5, 6};
            //das element mit dem Wert zustands_array[2] wird aus dem array auswahl_array gelöscht
            entferne_wert(std::auswahl_array, zustands_array[2]);
            //das element mit dem Wert 7-zustands_array[2] wird aus dem array auswahl_array gelöscht
            entferne_wert(std::auswahl_array, (7-zustands_array[2]));
            Serial.println("du kannst auf folgende Kanten aufstehen: %i, %i, %i, %i", auswahl_array[0], auswahl_array[1], auswahl_array[2], auswahl_array[3]);
            if(Serial.available()){char user_input = serial.read();}
            steuerung.flaeche_auf_kante(user_input);
        }
        else if (user_input == e)
        {   
            zustands_string = vector_to_string(zustands_array);
            switch zustands_string[2]
            {
                case 001: std::auswahl_array[4] = {23, 35, 45, 24};
                break;
                case 002: std::auswahl_array[4] = {36, 46, 14, 13};
                break;
                case 003: std::auswahl_array[4] = {26, 56, 15, 12};
                break;
                case 004: std::auswahl_array[4] = {12, 26, 56, 15};
                break;
                case 005: std::auswahl_array[4] = {36, 46, 14, 13};
                break;
                case 006: std::auswahl_array[4] = {23, 35, 45, 24};
                break;
                default: Serial.println("kein gültiges user_input");
                break;
            }
            Serial.println("du kannst auf folgende Ecken aufstehen: %i, %i, %i, %i", auswahl_array[0], auswahl_array[1], auswahl_array[2], auswahl_array[3]);
            if(Serial.available()){char user_input = serial.read();}
            steuerung.flaeche_auf_ecke(user_input);
        }
        else
        {
            Serial.println("kein gültiges user_input");
        }

    else if (zustands_array[0] == 0) //wir befinden uns auf Kante
    {
        Serial.println("Robo befindet sich auf Kante %i %i", zustands_array[1], zustands_array[2]);
        Serial.println("Zum aufstehen auf Ecke gebe e ein, zum herunterfallen auf eine Fläche f");
        if (Serial.available()){char user_input = serial.read();}
        if (user_input == f)
        {
            Serial.println("du kannst auf folgende Flächen abfallen: %i, %i", zustands_array[0], zustands_array[1]);
            if(Serial.available()){char user_input = serial.read();}
            steuerung.kante_auf_flaeche(user_input);
        }
        else if (user_input == e)
        {
            zustands_string = vector_to_string(zustands_array);
            switch zustands_string
            {
                case 012: std::auswahl_array[2] = {3, 4};
                break;
                case 013: std::auswahl_array[2] = {2, 5};
                break;
                case 014: std::auswahl_array[2] = {2, 5};
                break;
                case 015: std::auswahl_array[2] = {3, 4};
                break;
                case 062: std::auswahl_array[2] = {3, 4};
                break;
                case 063: std::auswahl_array[2] = {2 ,5};
                break;
                case 064: std::auswahl_array[2] = {2, 5};
                break;
                case 065: std::auswahl_array[2] = {3, 4};
                break;
                case 023: std::auswahl_array[2] = {1, 6};
                break;
                case 024: std::auswahl_array[2] = {1, 6};
                break;
                case 053: std::auswahl_array[2] = {1, 6};
                break;
                case 054: std::auswahl_array[2] = {1, 6};
                break;
                default: Serial.println("kein gültiges user_input");
                break;
            }
            Serial.println("du kannst auf folgende Ecken aufstehen: %i, %i", auswahl_array[0], auswahl_array[1]);
            if(Serial.available()){char user_input = serial.read();}
            steuerung.kante_auf_ecke(user_input);
        }
        else
        {
            Serial.println("kein gültiges user_input");
        }
    }
    else //wir befinden uns auf Ecke
    {
      Serial.print("Robo befindet sich auf Ecke");

        Serial.println("Zum herunterfallen auf Kante gebe k ein, zum herunterfallen auf eine Fläche f");
        if (Serial.available()){char user_input = serial.read();}
        if (user_input == k)
        {
            Serial.println("du kannst auf folgende Kanten abfallen: %i%i, %i%i, %i%i", zustands_array[0], zustands_array[1], zustands_array[1], zustands_array[2], zustands_array[0], zustands_array[2]);
            if(Serial.available()){char user_input = serial.read();}
            steuerung.ecke_auf_kante(user_input);
        }
        else if (user_input == f)
        {
            Serial.println("du kannst auf folgende Flächen abfallen: %i, %i, %i", zustands_array[0], zustands_array[1], zustands_array[2]);
            if(Serial.available()){char user_input = serial.read();}
            steuerung.ecke_auf_flaeche(user_input);
        }
        else
        {
            Serial.println("kein gültiges user_input");
        }
    }
}
from selenium.webdriver.common.action_chains import ActionChains
from selenium import webdriver
import io
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
import time
from spellchecker import SpellChecker
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
#selectionner le navigateur ainsi que la page souhaité
driver = webdriver.Chrome()
driver.get("https://www.projet-voltaire.fr/voltaire/com.woonoz.gwt.woonoz.Voltaire/Voltaire.html?returnUrl=www.projet-voltaire.fr/choix-parcours/&applicationCode=pv")
#se connect sur le projet voltaire avec votre mot de passe
print("Donnez moi votre nom d'utilisateur et puis votre mot de passe")
#nom_utilisateur=str(input())
#mot_de_passe=str(input())
time.sleep(3)
search_box = driver.find_element(By.ID, "user_pseudonym")
search_box.send_keys("raphael.croix@etud.univ-angers.fr")
search_box = driver.find_element(By.ID, "user_password")
search_box.send_keys("Angers24")
search_box.send_keys(Keys.RETURN)
#trouve le bon bouton du projet voltaire pour lancer la session, ps, si vous savez pas comment ça marche, juste effacez ces les lignes 24 25 26, et accedez manuellement au niveau où vous êtes et augmentez les sleeps en bat pour avoir le temps d'accéder au niveau
search_box = WebDriverWait(driver, 10).until(EC.visibility_of_element_located((By.XPATH, '//div[@class="validation-activity-cell-title" and text()="Validation des niveaux 5 à 7"]')))
actions = ActionChains(driver)
actions.move_to_element(search_box).click().perform()
time.sleep(40)
while True:
    faute=-1
    i=0
    spell = SpellChecker(language='fr')
    try:        
        #regarde si il y a un programme test d'entraînement et passe le truc
        test = WebDriverWait(driver, 0.2).until(EC.visibility_of_element_located((By.XPATH, '//div[@class="intensiveTrainingHeader"]')))
        test= WebDriverWait(driver,2).until(EC.visibility_of_element_located((By.XPATH, '//button[@class="understoodButton"]')))
        test.click()
        test= driver.find_elements(By.XPATH, '//button[@class="buttonOk"]')
        test[0].click()
        test[1].click()
        test[2].click()
        try:
            #si on a échoué
            test= driver.find_element(By.XPATH, '//button[@class="exitButton secondaryButton"]')
            test.click()
        except:
            #si on a réussi
            test= driver.find_element(By.XPATH, '//button[@class="exitButton primaryButton"]')
            test.click()

     
    except:
        try:
            # regarde s'il y a une vidéo d'entrainement et la passe
            test = WebDriverWait(driver, 0.2).until(EC.visibility_of_element_located((By.XPATH, '//button[@class="popupButton"]')))
            test.click()
        except:

            try:
                #si il y a un test où on a besoin découter, le passe, se trompe donc
                test = WebDriverWait(driver, 0.2).until(EC.visibility_of_element_located((By.XPATH, '//button[@class="validateButton"]')))
                test.click()
            except:
                #trouve les mots et l'erreur
                time.sleep(0.2)
                mot = driver.find_elements(By.XPATH, '//span[@class="pointAndClickSpan"]')
                while mot[i].text not in[".","?","!",""]:
                    if   mot[i].text not in spell and mot[i].text!='':
                        faute=i
                    i=i+1
                #clic sur l'erreur s'il y a une faute
                if faute !=-1:
                    search_box = mot[faute]
                    search_box.click()
                else:
                    #sinon clic sur pas d'erreur
                    search_box = WebDriverWait(driver, 10).until(EC.visibility_of_element_located((By.XPATH, '//button[@class="noMistakeButton"]')))
                    search_box.click()
                    #go next
            search_box = WebDriverWait(driver, 10).until(EC.visibility_of_element_located((By.XPATH, '//button[@class="nextButton"]')))
            search_box.click()

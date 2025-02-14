import numpy as np
import cv2
from scipy.ndimage import gaussian_filter

from matplotlib import pyplot as plt

#Lecture image en niveau de gris et conversion en float64
img=np.float64(cv2.imread('../Image_Pairs/Graffiti0.png',cv2.IMREAD_GRAYSCALE))
(h,w) = img.shape
print("Dimension de l'image :",h,"lignes x",w,"colonnes")
print("Type de l'image :",img.dtype)

#Début du calcul
t1 = cv2.getTickCount()
Theta = cv2.copyMakeBorder(img,0,0,0,0,cv2.BORDER_REPLICATE)
# Mettre ici le calcul de la fonction d'intérêt de Harris
# Calcul de Xi
W_size = 10
alpha = 0.06
sigma = 1

Ix = gaussian_filter(img, sigma, order=[1,0])
Iy = gaussian_filter(img, sigma, order=[0,1])
IxIy = np.multiply(Ix,Iy)

for x in range (h):
    for y in range(w):
        # Extract the sub-matrices corresponding to the window
        Ix_window = Ix[max(0,x-W_size//2):min(h,x+W_size//2), max(0,y-W_size//2):min(w,y+W_size//2)]
        # Ix_window = gaussian_filter(Ix_window, sigma = sigma_2)
        Iy_window = Iy[max(0,x-W_size//2):min(h,x+W_size//2), max(0,y-W_size//2):min(w,y+W_size//2)]
        # Iy_window = gaussian_filter(Iy_window, sigma = sigma_2)
        IxIy_window = IxIy[max(0,x-W_size//2):min(h,x+W_size//2), max(0,y-W_size//2):min(w,y+W_size//2)]
        # IxIy_window = gaussian_filter(IxIy_window, sigma = sigma_2)
        Xi_top_left = np.sum(np.square(Ix_window))
        Xi_top_right = np.sum(IxIy_window)
        Xi_bot_right = np.sum(np.square(Iy_window))
        Theta[x][y] = Xi_top_left*Xi_bot_right - Xi_top_right**2 - alpha*(Xi_top_left+Xi_bot_right)**2



# Calcul des maxima locaux et seuillage
Theta_maxloc = cv2.copyMakeBorder(Theta,0,0,0,0,cv2.BORDER_REPLICATE)
d_maxloc = 3
seuil_relatif = 0.01
se = np.ones((d_maxloc,d_maxloc),np.uint8)
Theta_dil = cv2.dilate(Theta,se)
#Suppression des non-maxima-locaux
Theta_maxloc[Theta < Theta_dil] = 0.0
#On néglige également les valeurs trop faibles
Theta_maxloc[Theta < seuil_relatif*Theta.max()] = 0.0
t2 = cv2.getTickCount()
time = (t2 - t1)/ cv2.getTickFrequency()
print("Mon calcul des points de Harris :",time,"s")
print("Nombre de cycles par pixel :",(t2 - t1)/(h*w),"cpp")

plt.subplot(131)
plt.imshow(img,cmap = 'gray')
plt.title('Image originale')

plt.subplot(132)
plt.imshow(Theta,cmap = 'gray')
plt.title('Fonction de Harris')

se_croix = np.uint8([[1, 0, 0, 0, 1],
[0, 1, 0, 1, 0],[0, 0, 1, 0, 0],
[0, 1, 0, 1, 0],[1, 0, 0, 0, 1]])
Theta_ml_dil = cv2.dilate(Theta_maxloc,se_croix)
#Relecture image pour affichage couleur
Img_pts=cv2.imread('../Image_Pairs/Graffiti0.png',cv2.IMREAD_COLOR)
(h,w,c) = Img_pts.shape
print("Dimension de l'image :",h,"lignes x",w,"colonnes x",c,"canaux")
print("Type de l'image :",Img_pts.dtype)
#On affiche les points (croix) en rouge
Img_pts[Theta_ml_dil > 0] = [255,0,0]
plt.subplot(133)
plt.imshow(Img_pts)
plt.title('Points de Harris')

plt.show()

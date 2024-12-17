import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv('PZEMraw.csv')

for i in range(1, 14, 1):
    #Calculates the slope and intercept of the line of best fit
    xstring = "PZEM"+str(i)
    ystring = "Multi"+str(i)

    corr_matrix = np.corrcoef(df[ystring], df[xstring])
    corr = corr_matrix[0, 1]
    R_sq = corr ** 2

    line = np.polyfit(df[xstring],df[ystring], 1)
    poly = np.poly1d(line)
    x = np.linspace(np.min(df[xstring]),np.max(df[xstring]),100)

    #Gives the relevant slope and y-intercept [m b]
    m = round(line[0],3)
    b = round(line[1],3)

    mu = 1
    sigma = 2
    textstr = r'$\mathrm{R^2}=%.2f$' % (R_sq,)

    #Plots the data and the calibration curve
    fig, ax = plt.subplots()
    plt.scatter(df[xstring],df[ystring])
    plt.plot(x, poly(x),'r', label='y={}x+({})'.format(m,b))
    plt.xlabel("PZEM"+str(i)+" Sensor Reading [V]")
    plt.ylabel('Multimeter Reading [V]')
    plt.title("Linear Regression for PZEM"+str(i))
    plt.legend(loc='center right')
    ax.text(0.05, 0.95, textstr, transform=ax.transAxes, fontsize=14,
            verticalalignment='top')
    plt.show()
#船型系数计算
#船厂 L:  L_pp:垂线间长  L_OA:船总长  L_WL:水线间长
#

def ship_factor(l,b,d,D,Aw,Am,v):
    save={'l':l,'b':b,'d':d,
          'Aw':Aw,'Am':Am,'v':v,
          'C_wp':Aw/(l*b),'C_m':Am/(b*d),'C_b':v/(l*b*d),'C_p':v/(Am*l),'C_vp':v/(Aw*d),
          'l/b':l/b,'b/d':b/d,'b/D':b/D,'l/D':l/D,'D/d':D/d}
    print('''型长：           %f\n型宽：           %f\n吃水：           %f
水线面系数C_wp:   %f\n中横剖面系数C_m:  %f\n方形系数C_b:      %f\n菱形系数C_p:      %f\n纵向菱形系数C_vp:  %f
长宽比L/B:       %f\n宽度吃水比b/d:    %f\n型深吃水比D/d:    %f\n长深比l/D:       %f'''
          %(l,b,d,save['C_wp'],save['C_m'],save['C_b'],save['C_p'],save['C_vp'],
            save['l/b'],save['b/d'],save['D/d'],save['l/D']))


ship_factor(12,33,54,56,32.1,4,2)

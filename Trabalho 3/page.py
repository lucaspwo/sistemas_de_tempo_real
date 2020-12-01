import streamlit as st
import json

path = '/home/pi/str/'

var = json.loads(open(path + 'var.json').read())

st.title('Painel de Controle de Velocidade')

st.write('<style>div.Widget.row-widget.stRadio > div{flex-direction:row;}</style>', unsafe_allow_html=True)

var['t1'] = int(st.radio('Trem 1', ('1', '2', '3', '4', '5')))
var['t2'] = int(st.radio('Trem 2', ('1', '2', '3', '4', '5')))
var['t3'] = int(st.radio('Trem 3', ('1', '2', '3', '4', '5')))
var['t4'] = int(st.radio('Trem 4', ('1', '2', '3', '4', '5')))

f = open(path + 'var.json','w')
f.write(json.dumps(var))
f.close()
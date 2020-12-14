import streamlit as st
import socket

serverAddr = '192.168.1.233'
serverPort = 2310
s = socket.socket()

t1 = 0
t2 = 0
t3 = 0
t4 = 0

st.title('Painel de Controle de Velocidade')

st.write('<style>div.Widget.row-widget.stRadio > div{flex-direction:row;}</style>', unsafe_allow_html=True)

t1 = int(st.radio('Trem 1', ('1', '2', '3', '4', '5')))
t2 = int(st.radio('Trem 2', ('1', '2', '3', '4', '5')))
t3 = int(st.radio('Trem 3', ('1', '2', '3', '4', '5')))
t4 = int(st.radio('Trem 4', ('1', '2', '3', '4', '5')))

message = st.empty()

if st.button('Enviar'):
    vel = [t1, t2, t3, t4]
    b_vel = str.encode(str(vel))
    s.connect((serverAddr, serverPort))
    s.send(b_vel)
    message.success('Enviado!')
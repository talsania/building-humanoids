import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/kptal/humanoid_ws/install/dual_arm_ik_solver'

import subprocess
import time

def ensure_can_interface(interface="can0", bitrate=50000, is_virtual=False):
    def interface_exists():
        result = subprocess.run(["ip", "link", "show", interface], capture_output=True, text=True)
        return result.returncode == 0

    def interface_is_up():
        result = subprocess.run(["ip", "link", "show", interface], capture_output=True, text=True)
        return "state UP" in result.stdout

    if not interface_exists():
        if is_virtual:
            print(f"[INFO] Creating virtual CAN interface '{interface}'...")
            subprocess.run(["sudo", "modprobe", "vcan"], check=True)
            subprocess.run(["sudo", "ip", "link", "add", "dev", interface, "type", "vcan"], check=True)
        else:
            raise RuntimeError(f"CAN interface '{interface}' does not exist. Check your hardware.")

    if not is_virtual:
        # Shut down if it's already up
        subprocess.run(["sudo", "ip", "link", "set", interface, "down"], check=True)
        # Set bitrate
        print(f"[INFO] Setting bitrate for '{interface}' to {bitrate} bps...")
        subprocess.run(["sudo", "ip", "link", "set", interface, "type", "can", "bitrate", str(bitrate)], check=True)

    # Bring interface up
    subprocess.run(["sudo", "ip", "link", "set", interface, "up"], check=True)
    time.sleep(0.5)

    print(f"[OK] CAN interface '{interface}' is up with bitrate {bitrate} bps.")

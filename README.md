# PID Based Line Follower Robot

## Overview
This project demonstrates an autonomous line follower robot powered by a PID control system. Using an IR sensor array, the robot continuously estimates the position of a black tape track and computes the tracking error in real time. The PID controller converts this error into smooth motor corrections, enabling accurate and stable navigation.

The robot is optimized for performance: it runs at higher speeds on straight sections and automatically reduces speed while handling curves and sharp turns.

To ensure reliability across different surfaces and lighting conditions, the robot performs a 6-second automatic calibration routine at startup. A buzzer melody confirms the completion of calibration and readiness of the system.

## Concepts Used

### 1. Automatic Sensor Calibration

On every startup, the robot performs an automatic calibration routine. Each IR sensor records its minimum and maximum readings over the calibration period.

These values are then used to normalize sensor outputs:

`normalized[i] = map(raw[i], min[i], max[i], 0, 1000)`

This makes the system robust to changes in surface color, lighting conditions, and sensor variations.

------
### 2. 7-Channel Weighted Line Position Estimation

The robot uses a 7-channel analog IR sensor array to detect the line. Each sensor is assigned a positional weight to represent its location relative to the center of the robot:

`S0  S1  S2  S3  S4  S5  S6 `

`-3  -2  -1   0  +1  +2  +3`


A weighted average method is used to compute a fine, continuous estimate of the line position:

`error = Σ(normalized[i] × weight[i]) / Σ(normalized[i])`

This provides smooth and precise center detection instead of rough left/right decisions.

-----
### 3. PID-Based Steering Control

The computed error is fed into a PID controller:

P (Proportional) → corrects based on how far the robot is from the line

I (Integral) → compensates for long-term bias and steady-state error

D (Derivative) → dampens oscillations and improves stability

The PID output continuously adjusts the left and right motor speeds to maintain accurate tracking.

------
### 4. Line Lost Detection & Recovery

If none of the sensors detect the line, the robot identifies this as a “line lost” condition. It then:

Reduces speed

Turns in the last known direction of the line

This increases the probability of quickly reacquiring the track instead of moving blindly.

------
### 5. Dynamic Base Speed Control

The robot adapts its base speed based on the magnitude of the error:

Small error (straight line) → higher speed

Large error (curves/turns) → reduced speed

This allows fast motion on straight sections while maintaining control and stability on sharp curves.


## Design Considerations & Good Practices

### 1. Real-Time Control Loop

Since PID control depends on real-time feedback, no delay() functions are used inside the main control loop. This ensures high update frequency, low latency, and stable controller behavior.


### 2. Proper Sensor Placement

The IR sensor array is mounted approximately 6–9 mm above the ground to ensure strong contrast between the black line and the background. Improper sensor height or alignment leads to unreliable readings, which result in incorrect error estimation and unstable control.


### 3. Bounded PID Output & Windup Prevention

The PID output is constrained within the valid PWM range (0–255) before being applied to the motors. This prevents excessive actuator commands and reduces the risk of integral windup and motor saturation.

### 4. Mechanical Stability

The robot is designed to be:

Lightweight

Low center of mass

Rigidly mounted sensor array

Sensor placed slightly ahead of the wheels

This improves responsiveness, reduces vibration-induced noise, and makes the control system more predictable.


### 5. Comprehensive Testing Strategy

The robot is tested on multiple track types:

Straight paths

S-curves

Sharp turns

Disturbance tests (manual pushes, partial line loss, etc.)

This ensures robustness and consistent performance under different conditions.


### 6. Environment-Invariant Calibration

Automatic calibration is implemented so the same PID parameters can work across different surfaces and lighting conditions, minimizing the need for retuning.


### 7. Safe PID Tuning Methodology

PID tuning is performed at low motor speeds first to ensure stability. Once reliable behavior is achieved, the base speed is gradually increased to achieve high-speed performance.

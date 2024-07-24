<!DOCTYPE html>
<h1>Cab Pooling System for University Students</h1>

<h2>Problems Generally Faced While Travelling</h2>
<ul>
    <li>Students often face high cab costs for distant exams or events.</li>
    <li>Many students travel alone without knowing others going to the same destination and end up spending a lot on cabs.</li>
    <li>Shuttle services in a college are limited to only certain places and the timings do not coordinate with everyone’s schedule.</li>
    <li>Wouldn’t it be better if you could share cabs and split the fare with fellow university students?</li>
</ul>

<h2>One-Step Solution</h2>
<p>Implementing a cab pooling system for university students.</p>

<h2>Approach</h2>
<p>Defined a specific format for the people to input their schedules. The format includes all the details like departure time, destination, and contact information (email). Used SQL based databases like MySQL for storing the data.</p>
<p>The C++ program written, using a database, creates a class for user data and schedules. Algorithms, including graph and backtracking, match schedules based on criteria like destination and departure time, optimizing for efficiency are used. Considerations include dropping off passengers, restricting destinations within +-2km, and prioritizing identical destinations using a database search algorithm.</p>
<p>Once the matches are found, the people are notified via an email and contact information for each other about the possibility of sharing a cab. This is achieved by routing the output from the C++ program to an input for a python script, which would use an API service to send out the emails.</p>

<h2>Benefits</h2>
<div class="benefits">
    <ul>
        <li>Connects students with shared travel routes to save money and reduce travel expenses.</li>
        <li>Aims to alleviate financial strain and promote a collaborative approach to commuting.</li>
        <li>Cost-saving: Sharing cab expenses with fellow students.</li>
        <li>Convenience: Easier travel arrangements, especially for distant destinations.</li>
        <li>Community building: Encourages collaboration and social interaction among students.</li>
        <li>Enhancing transportation outside university and improving the university experience for all students.</li>
    </ul>
</div>

</body>
</html>
